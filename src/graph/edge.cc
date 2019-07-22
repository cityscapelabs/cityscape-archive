#include "edge.h"

//! Constructor with source and destination nodes and a unique edge id
cityscape::graph::Edge::Edge(
    const std::shared_ptr<cityscape::graph::Node>& src,
    const std::shared_ptr<cityscape::graph::Node>& dest, cityscape::id_t id,
    const std::string& tag)
    : id_{id} {
  src_ = src;
  dest_ = dest;
  // If not an empty tag, insert tag
  if (!tag.empty()) tags_.insert(tag);
}

//! Edge id
cityscape::id_t cityscape::graph::Edge::id() const { return id_; }

//! Check if the edge has a specific tag
bool cityscape::graph::Edge::check_tag(const std::string& tag) const {
  return (tags_.find(tag) != tags_.end() ? true : false);
}

//! Get edge weight
double cityscape::graph::Edge::weight() const { return weight_; }

//! Assign edge weight
void cityscape::graph::Edge::weight(double weight) { weight_ = weight; }
