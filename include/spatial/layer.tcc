#include "layer.h"

template <typename P>
bool Layer<P>::add_node(const std::shared_ptr<P>& point) {
  bool status = true;
  try {
    // Insert if point is not found in the graph
    if (nodes_names_.find(point->name()) == nodes_names_.end()) {
      auto nid = point->id();
      points_.emplace(std::make_pair(nid, point));
      point_index_->insert(point);
      // add to graph
      nodes_.emplace(std::make_pair(nid, point));
      nodes_names_.emplace(std::make_pair(point->name(), nid));

    } else {
      throw std::runtime_error("Duplicate points found, insertion failed");
    }
  } catch (std::exception& exception) {
    status = false;
  }
  return status;
}

template <typename P>
bool Layer<P>::create_edge(const std::string& src, const std::string& dest,
                           bool directed, const std::string& tag) {
  bool edge_status = true;
  try {
    if (src == dest)
      throw std::runtime_error("Source and destination are identical");

    auto src_id = nodes_names_.at(src);
    auto dest_id = nodes_names_.at(dest);
    auto source = points_.at(src_id);
    auto destination = points_.at(dest_id);

    // Create a new edge index
    auto eid = edge_idx_.create_index();
    auto segment = std::make_shared<Segment<P>>(source, destination, eid, tag);

    segment_index_->insert(segment);
    segments_.emplace(
        std::make_pair(std::make_tuple(src_id, dest_id), segment));
    segment_ids_.emplace(std::make_pair(eid, segment));
    // add to edges as well
    edges_.emplace(std::make_pair(std::make_tuple(src_id, dest_id), segment));
    edge_ids_.emplace(std::make_pair(eid, segment));

    // Directed graph
    if (directed) {
      source->add_edge(segment, cityscape::graph::Direction::Outgoing);
      destination->add_edge(segment, cityscape::graph::Direction::Incoming);
    } else {
      // Undirected graph
      source->add_edge(segment, cityscape::graph::Direction::Any);
      destination->add_edge(segment, cityscape::graph::Direction::Any);
      segments_.emplace(
          std::make_pair(std::make_tuple(src_id, dest_id), segment));
      edges_.emplace(std::make_pair(std::make_tuple(dest_id, src_id), segment));
    }
  } catch (std::exception& exception) {
    edge_status = false;
    std::cout << "Exception: " << exception.what() << "\n";
  }
  return edge_status;
}

template <typename P>
std::shared_ptr<Segment<P>> Layer<P>::segment(cityscape::id_t src,
                                              cityscape::id_t dest) {
  std::shared_ptr<Segment<P>> segment = nullptr;
  try {
    // Locate segment in layer
    auto eitr = segments_.find(std::make_tuple(src, dest));
    if (eitr != segments_.end())
      segment = (*eitr).second;
    else
      throw std::runtime_error(
          "Invalid segment, does not exist, returning nullptr\n");
  } catch (std::exception& exception) {
    std::cout << "Exception: " << exception.what() << "\n";
  }
  return segment;
}
