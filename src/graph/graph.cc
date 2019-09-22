#include "graph.h"
#include <iostream>

//! Constructor with a unique graph id, tag and initialize idx
cityscape::graph::Graph::Graph(cityscape::id_t id, const std::string& tag)
    : id_{id}, node_idx_{0}, edge_idx_{0} {
  // If not an empty tag, insert tag
  if (!tag.empty()) tags_.insert(tag);
}

//! Graph id
cityscape::id_t cityscape::graph::Graph::id() const { return id_; }

//! Check if the graph has a specific tag
bool cityscape::graph::Graph::check_tag(const std::string& tag) const {
  return (tags_.find(tag) != tags_.end() ? true : false);
}

//! Add node
bool cityscape::graph::Graph::add_node(const std::shared_ptr<Node>& node) {
  bool add_node_status = true;
  try {
    // Insert if node is not found in the graph
    if (nodes_names_.find(node->name()) == nodes_names_.end()) {
      auto nid = node_idx_.create_index();
      nodes_.emplace(std::make_pair(nid, node));
      nodes_names_.emplace(std::make_pair(node->name(), nid));
    } else {
      throw std::runtime_error("Duplicate node found, insertion failed");
    }
  } catch (std::exception& exception) {
    add_node_status = false;
  }
  return add_node_status;
}

//! Number of nodes
cityscape::id_t cityscape::graph::Graph::nnodes() const {
  return nodes_.size();
}

//! create edge
bool cityscape::graph::Graph::create_edge(const std::string& src,
                                          const std::string& dest,
                                          bool directed,
                                          const std::string& tag) {
  bool edge_status = true;
  try {
    if (src == dest)
      throw std::runtime_error("Source and destination are identical");

    auto src_id = nodes_names_.at(src);
    auto dest_id = nodes_names_.at(dest);
    auto source = nodes_.at(src_id);
    auto destination = nodes_.at(dest_id);

    // Create a new edge index
    auto eid = edge_idx_.create_index();
    auto edge =
        std::make_shared<cityscape::graph::Edge>(source, destination, eid, tag);
    edges_.emplace(std::make_pair(std::make_tuple(src_id, dest_id), edge));

    // Directed graph
    if (directed) {
      source->add_edge(edge, cityscape::graph::Direction::Outgoing);
      destination->add_edge(edge, cityscape::graph::Direction::Incoming);
    } else {
      // Undirected graph
      source->add_edge(edge, cityscape::graph::Direction::Any);
      destination->add_edge(edge, cityscape::graph::Direction::Any);
      edges_.emplace(std::make_pair(std::make_tuple(dest_id, src_id), edge));
    }
  } catch (std::exception& exception) {
    edge_status = false;
    std::cout << "Exception: " << exception.what() << "\n";
  }
  return edge_status;
}

//! Number of edges
cityscape::id_t cityscape::graph::Graph::nedges() const {
  return edges_.size();
}

//! Return an edge pointer
std::shared_ptr<cityscape::graph::Edge> cityscape::graph::Graph::edge(
    cityscape::id_t src, cityscape::id_t dest) const {

  std::shared_ptr<cityscape::graph::Edge> edge = nullptr;
  try {
    // Locate edge in graph
    auto eitr = edges_.find(std::make_tuple(src, dest));
    if (eitr != edges_.end())
      edge = (*eitr).second;
    else
      throw std::runtime_error(
          "Invalid edge, does not exist, returning nullptr\n");
  } catch (std::exception& exception) {
    std::cout << "Exception: " << exception.what() << "\n";
  }
  return edge;
}

// Dijktra shortest paths from src to a vertex
std::vector<cityscape::id_t> cityscape::graph::Graph::dijkstra(
    const std::string& src, const std::string& dest) const {

  cityscape::id_t source = nodes_names_.at(src);
  cityscape::id_t destination = nodes_names_.at(dest);

  // Using lambda to compare elements.
  auto compare =
      [](std::pair<cityscape::graph::weight_t, cityscape::id_t> left,
         std::pair<cityscape::graph::weight_t, cityscape::id_t> right) {
        return left.first > right.first;
      };

  // Create a priority queue to store weights and vertices
  std::priority_queue<
      std::pair<cityscape::graph::weight_t, cityscape::id_t>,
      std::vector<std::pair<cityscape::graph::weight_t, cityscape::id_t>>,
      decltype(compare)>
      priority_queue(compare);

  // Create a vector for distances and initialize all to max
  std::vector<graph::weight_t> distances;
  distances.resize(this->nodes_.size(),
                   std::numeric_limits<cityscape::graph::weight_t>::max());
  // Parent array to store shortest path tree
  std::vector<cityscape::id_t> parent;
  parent.resize(this->nodes_.size(), -1);

  std::vector<cityscape::id_t> path;
  if (nodes_.find(source) == nodes_.end() ||
      nodes_.find(destination) == nodes_.end())
    return path;

  // Insert source itself in priority queue & initialize its distance as 0.
  priority_queue.push(std::make_pair(0., source));
  distances[source] = 0.;

  // Looping till priority queue becomes empty (or all
  // distances are not finalized)
  while (!priority_queue.empty()) {
    // {min_weight, vertex} sorted based on weights (distance)
    cityscape::id_t u = priority_queue.top().second;
    priority_queue.pop();

    // Break if destination is reached
    if (u == destination) break;

    // Get all adjacent vertices of a vertex
    for (const auto& edge : nodes_.at(u)->out_edges()) {
      // Get node id of neighbour of u.
      const cityscape::id_t neighbour = edge->dest()->id();

      // Distance from source to neighbour
      // distance_u = distance to current node + weight of edge u to
      // neighbour
      const cityscape::graph::weight_t distance_u =
          distances.at(u) + edge->weight();
      // If there is shorted path to neighbour vertex through u.
      if (distances.at(neighbour) > distance_u) {
        parent[neighbour] = u;
        // Update distance of the vertex
        distances.at(neighbour) = distance_u;
        priority_queue.push(std::make_pair(distance_u, neighbour));
      }
    }
  }

  path.emplace_back(destination);
  // Iterate until source has been reached
  while (destination != source && destination != -1) {
    destination = parent.at(destination);
    if (destination != source && destination != -1)
      path.emplace_back(destination);
  }
  path.emplace_back(source);
  // Reverse to arrange path from source to destination
  std::reverse(std::begin(path), std::end(path));

  // double cost = 0;
  // for (cityscape::id_t i = 0; i < path.size() - 1; ++i) {
  //   cost += edges_.at(std::make_tuple(path[i], path[i + 1]))->weight();
  //   std::cout << "Edge: " << path[i] << " -> " << path[i + 1] << " cost: "
  //             << edges_.at(std::make_tuple(path[i], path[i + 1]))->weight()
  //             << std::endl;
  // }
  // std::cout << "Path cost: " << cost << std::endl;

  return path;
}
