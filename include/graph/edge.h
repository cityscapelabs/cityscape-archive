#ifndef CITYSCAPE_GRAPH_EDGE_H_
#define CITYSCAPE_GRAPH_EDGE_H_

#include <memory>
#include <set>

#include "node.h"
#include "types.h"

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
  //! \param[in] tag Tag to categorize edge (default is empty)
  Edge(const std::shared_ptr<cityscape::graph::Node>& src,
       const std::shared_ptr<cityscape::graph::Node>& dest, cityscape::id_t id,
       const std::string& tag = std::string());

  //! Edge id
  //! \retval id_ Id of the edge
  cityscape::id_t id() const;

  //! Check if the edge has a specific tag
  bool check_tag(const std::string& tag) const;

 private:
  //! Edge id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
  //! Source node
  std::shared_ptr<cityscape::graph::Node> src_;
  //! Destination node
  std::shared_ptr<cityscape::graph::Node> dest_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_EDGE_H_
