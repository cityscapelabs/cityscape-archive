#ifndef CITYSCAPE_SPATIAL_INDEX_MANAGER_H
#define CITYSCAPE_SPATIAL_INDEX_MANAGER_H

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "point.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

namespace boost {
namespace geometry {
namespace index {

// indexable to store pointers in rtree
template <typename Leaf>
struct indexable<std::shared_ptr<Leaf>> {
  typedef std::shared_ptr<Leaf> V;

  typedef Leaf const& result_type;
  result_type operator()(V const& v) const { return *v; }
};
}  // namespace index
}  // namespace geometry
};  // namespace boost

namespace cityscape {
namespace spatial {
namespace bgi = boost::geometry::index;

// using rtree_leaf_point = std::shared_ptr<cityscape::spatial::Point>;
// using rtree_index = bgi::rtree<rtree_leaf_point, bgi::rstar<4, 2>>;

//! Spatial index class
//! \brief Base class of a spatial index (point)
template <typename Leaf>
class SpatialIndex {
 public:
  //! Default constructor, construct index value by value
  SpatialIndex() = default;

  //! Construct spatial index through packing algorithm
  explicit SpatialIndex(const std::vector<Leaf>& values);

  //! Insert a point
  void insert(const Leaf& leaf);

  //! K nearest neighbor query
  //! \param[in] query_point point need to be queried
  //! \param[in] k number of nearest neighbor
  //! \param[out] query_result knn query result
  std::vector<Leaf> knn(const cityscape::spatial::Point& query_point,
                        unsigned k);

  //! size of the index
  id_t size() const { return indexer_.size(); }

 private:
  //! rtree for spatial index
  bgi::rtree<Leaf, bgi::rstar<4, 2>> indexer_;
};
#include "spatial_index.tcc"
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_INDEX_H_
