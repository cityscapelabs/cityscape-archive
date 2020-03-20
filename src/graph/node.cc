#include "node.h"

//! Constructor with unique node id, tag and name
cityscape::graph::Node::Node(cityscape::id_t id, const std::string& name,
                             const std::string& tag)
    : id_{id} {
  // If not an empty tag, insert tag
  if (!tag.empty()) tags_.insert(tag);
  // If name is empty, use id as name or assign name
  name_ = (name.empty() ? std::to_string(id) : name);
}

//! Node id
cityscape::id_t cityscape::graph::Node::id() const { return id_; }

//! Check if the node has a specific tag
bool cityscape::graph::Node::check_tag(const std::string& tag) const {
  return (tags_.find(tag) != tags_.end() ? true : false);
}

//! Return name
std::string cityscape::graph::Node::name() const { return name_; }

//! Add edge to node
void cityscape::graph::Node::add_edge(
    const std::shared_ptr<cityscape::graph::Edge>& edge, Direction dir) {
  // Incoming edge
  if (dir == cityscape::graph::Direction::Incoming)
    in_edges_.emplace_back(edge);
  // Outgoing edge
  else if (dir == cityscape::graph::Direction::Outgoing)
    out_edges_.emplace_back(edge);
  // Any direction
  else {
    in_edges_.emplace_back(edge);
    out_edges_.emplace_back(edge);
  }
  degree_ += 1;
}

//! Add tag to node
void cityscape::graph::Node::add_tag(const std::string& tag) {
  if (!tag.empty()) tags_.insert(tag);
}

//! Return outgoing edges
std::vector<std::shared_ptr<cityscape::graph::Edge>>
    cityscape::graph::Node::out_edges() const {
  return out_edges_;
}
