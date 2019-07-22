#ifndef CITYSCAPE_GRAPH_GRAPH_H_
#define CITYSCAPE_GRAPH_GRAPH_H_

#include "node.h"
#include "edge.h"

namespace cityscape {
namespace graph {

//! Graph class
//! \brief Base class of graph
class Graph {
 public:
  //! Constructor with a unique graph id and tag
  //! \param[in] id Index of the graph
  //! \param[in] tag Tag to categorize graph (default is empty)
  Graph( cityscape::id_t id,
       const std::string& tag = std::string());

  //! Graph id
  //! \retval id_ Id of the graph
  cityscape::id_t id() const;

  //! Check if the graph has a specific tag
  bool check_tag(const std::string& tag) const;

 private:
  //! Graph id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_GRAPH_H_
