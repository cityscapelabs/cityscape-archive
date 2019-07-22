#ifndef CITYSCAPE_GRAPH_NODE_H_
#define CITYSCAPE_GRAPH_NODE_H_

#include <memory>
#include <vector>

#include "types.h"

namespace cityscape {
namespace graph {
//! Forward declaration
//! Graph edge class
class Edge;

//! Graph node class
//! \brief Base class of a graph node (vertex)
class Node {
  //! Constructor with unique node id
  explicit Node(cityscape::id_t id) : id_{id} {};

  //! Node id
  cityscape::id_t id() { return id_; }

 private:
  //! Node id
  cityscape::id_t id_;
  //! In-edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> in_edges_;
  //! Out-edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> out_edges_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_NODE_H_
