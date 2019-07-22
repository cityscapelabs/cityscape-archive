#ifndef CITYSCAPE_GRAPH_EDGE_H_
#define CITYSCAPE_GRAPH_EDGE_H_

#include <memory>

#include "types.h"
#include "node.h"

namespace cityscape {
namespace graph {

//! Graph edge class
//! \brief Base class of a graph edge
class Edge {
 public:
  //! Constructor with source and destination nodes and a unique edge id
  //! \param[in] src Source node pointer
  //! \param[in] dest Destination node pointer
  //! \param[in] id Index of the edge
  Edge(const std::shared_ptr<cityscape::graph::Node>& src,
       const std::shared_ptr<cityscape::graph::Node>& dest,
       cityscape::id_t id);

  //! Edge id
  //! \retval id_ Id of the edge
  cityscape::id_t id() const;

 private:
  //! Edge id
  cityscape::id_t id_;
  //! Source node
  std::shared_ptr<cityscape::graph::Node> src_;
  //! Destination node
  std::shared_ptr<cityscape::graph::Node> dest_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_EDGE_H_
