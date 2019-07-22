#include "node.h"

//! Constructor with unique node id
cityscape::graph::Node::Node(cityscape::id_t id, const std::string& tag)
    : id_{id} {
  // If not an empty tag, insert tag
  if (!tag.empty()) tags_.insert(tag);
}

//! Node id
cityscape::id_t cityscape::graph::Node::id() const { return id_; }

//! Check if the node has a specific tag
bool cityscape::graph::Node::check_tag(const std::string& tag) const {
  return (tags_.find(tag) != tags_.end() ? true : false);
}
