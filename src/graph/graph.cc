#include "graph.h"

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
