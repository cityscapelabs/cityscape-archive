#include "edge.h"

//! Constructor with source and destination nodes and a unique edge id
cityscape::graph::Edge::Edge(
    const std::shared_ptr<cityscape::graph::Node>& src,
    const std::shared_ptr<cityscape::graph::Node>& dest, cityscape::id_t id)
    : id_{id} {
  src_ = src;
  dest_ = dest;
}

//! Edge id
cityscape::id_t cityscape::graph::Edge::id() const { return id_; }
