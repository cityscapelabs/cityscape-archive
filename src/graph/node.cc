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
