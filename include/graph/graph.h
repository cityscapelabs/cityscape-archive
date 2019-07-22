#ifndef CITYSCAPE_GRAPH_GRAPH_H_
#define CITYSCAPE_GRAPH_GRAPH_H_

#include "edge.h"
#include "index_manager.h"
#include "node.h"

namespace cityscape {
namespace graph {

//! Graph class
//! \brief Base class of graph
class Graph {
 public:
  //! Constructor with a unique graph id, tag and initialize idx
  //! \param[in] id Index of the graph
  //! \param[in] tag Tag to categorize graph (default is empty)
  Graph(cityscape::id_t id, const std::string& tag = std::string());

  //! Graph id
  //! \retval id_ Id of the graph
  cityscape::id_t id() const;

  //! Check if the graph has a specific tag
  bool check_tag(const std::string& tag) const;

  //! Add node
  

 private:
  //! Graph id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
  //! Node ID manager
  cityscape::IndexManager node_idx_;
  //! Edge ID manager
  cityscape::IndexManager edge_idx_;
  //! Nodes
  std::vector<std::shared_ptr<cityscape::graph::Node>> nodes_;
  //! Edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> edges_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_GRAPH_H_
