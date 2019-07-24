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
