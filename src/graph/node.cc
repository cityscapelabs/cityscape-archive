#include "node.h"

namespace cityscape {
namespace graph {

//! Constructor with unique node id
Node::Node(cityscape::id_t id) : id_{id} {};

//! Node id
cityscape::id_t Node::id() const { return id_; }
}  // namespace graph
}  // namespace cityscape
