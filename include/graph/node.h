#ifndef CITYSCAPE_GRAPH_NODE_H_
#define CITYSCAPE_GRAPH_NODE_H_

#include <limits>
#include <memory>
#include <set>
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
 public:
  //! Constructor with unique node id
  //! \param[in] id Index of the edge
  //! \param[in] tag Tag to categorize edge (default is empty)
  explicit Node(cityscape::id_t id, const std::string& tag = std::string());

  //! Node id
  cityscape::id_t id() const;

  //! Check if the edge has a specific tag
  bool check_tag(const std::string& tag) const;

 private:
  //! Node id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
  //! In-edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> in_edges_;
  //! Out-edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> out_edges_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_NODE_H_
