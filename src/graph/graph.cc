#include "graph.h"

//! Constructor with a unique graph id and tag
cityscape::graph::Graph::Graph(cityscape::id_t id, const std::string& tag)
    : id_{id} {
  // If not an empty tag, insert tag
  if (!tag.empty()) tags_.insert(tag);
}

//! Graph id
cityscape::id_t cityscape::graph::Graph::id() const { return id_; }

//! Check if the graph has a specific tag
bool cityscape::graph::Graph::check_tag(const std::string& tag) const {
  return (tags_.find(tag) != tags_.end() ? true : false);
}
