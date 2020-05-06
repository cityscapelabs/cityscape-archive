#ifndef CITYSCAPE_GRAPH_GRAPH_H_
#define CITYSCAPE_GRAPH_GRAPH_H_

#include <iostream>
#include <map>
#include <queue>

#include "tsl/robin_map.h"

#include "edge.h"
#include "index_manager.h"
#include "node.h"

namespace cityscape {
namespace graph {

//! Graph class
//! \brief Base class of graph
class Graph {
 public:
  //! Container type
  enum Container { Nodes, Edges };

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
  //! \param[in] node Pointer to node object
  bool add_node(const std::shared_ptr<Node>& node);

  //! Number of nodes
  cityscape::id_t nnodes() const;

  //! Create edge
  //! \param[in] src Source node name
  //! \param[in] dest Destination node name
  //! \param[in] directed Edge is directed or undirected
  //! \param[in] tag Tag to categorize edge (default is empty)
  bool create_edge(const std::string& src, const std::string& dest,
                   bool directed, const std::string& tag = std::string());

  //! Number of edges
  cityscape::id_t nedges() const;

  virtual  //! Return an edge pointer
      //! \param[in] src Source node id
      //! \param[in] dest Destination node id
      //! \retval edge Edge pointer
      std::shared_ptr<cityscape::graph::Edge>
      edge(cityscape::id_t src, cityscape::id_t dest) const;

  //! Compute the shortest path using priority queue
  //! \param[in] src Source node name
  //! \param[in] dest Destination node name
  //! \param[in] ctr Container type (default is edges)
  //! \retval path Vertices of the path from source to destination
  std::vector<cityscape::id_t> dijkstra(const std::string& src,
                                        const std::string& dest,
                                        Container ctr = Container::Edges) const;

  // Compute cost of shortest paths from src to a vertex
  //! \param[in] path Vector of vertices or edges (default is edges)
  //! \param[in] ctr Container type (default is edges)
  //! \retval cost Cost of the path
  double path_cost(const std::vector<cityscape::id_t>& path,
                   Container ctr = Container::Edges) const;

 protected:
  //! Graph id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
  //! Edge ID manager
  cityscape::IndexManager edge_idx_;
  //! Nodes
  tsl::robin_map<cityscape::id_t, std::shared_ptr<cityscape::graph::Node>>
      nodes_;
  //! Nodes and names key
  tsl::robin_map<std::string, cityscape::id_t> nodes_names_;
  // Edges
  std::map<std::tuple<cityscape::id_t, cityscape::id_t>,
           std::shared_ptr<cityscape::graph::Edge>>
      edges_;
  // Edges
  tsl::robin_map<cityscape::id_t, std::shared_ptr<cityscape::graph::Edge>>
      edge_ids_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_GRAPH_H_
