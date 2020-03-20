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

//! Direction
enum Direction { Any, Outgoing, Incoming };

//! Graph node class
//! \brief Base class of a graph node (vertex)
class Node {
 public:
  //! Constructor with unique node id
  //! \param[in] id Index of the edge
  //! \param[in] name Unique name of the node
  //! \param[in] tag Tag to categorize node (default is empty)
  Node(cityscape::id_t id, const std::string& name,
       const std::string& tag = std::string());

  //! Node id
  cityscape::id_t id() const;

  //! Check if the edge has a specific tag
  //! \param[in] tag Tag to categorize node
  bool check_tag(const std::string& tag) const;

  //! Return name
  std::string name() const;

  //! Return tag
  std::set<std::string> tag() const { return tags_; }

  //! Return connectivity degree
  cityscape::id_t connect_degree() const { return degree_; }

  //! Add edge
  //! \param[in] edge Edge pointer
  //! \param[in] dir Direction of edge
  void add_edge(const std::shared_ptr<cityscape::graph::Edge>& edge,
                Direction dir);

  //! Add tag
  //! \param[in] tag New tag
  void add_tag(const std::string& tag);

  //! Out edges
  //! \retval out_edges Return vector of outgoing edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> out_edges() const;

 protected:
  //! Node id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
  //! Name
  std::string name_;
  //! Connectivity degree
  cityscape::id_t degree_;
  //! In-edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> in_edges_;
  //! Out-edges
  std::vector<std::shared_ptr<cityscape::graph::Edge>> out_edges_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_NODE_H_
