#ifndef CITYSCAPE_SPATIAL_INDEX_MANAGER_H
#define CITYSCAPE_SPATIAL_INDEX_MANAGER_H

#include "point.h"
#include <boost/geometry/index/rtree.hpp>

namespace cityscape {
namespace spatial {
namespace bgi = boost::geometry::index;

using rtree_leaf_point = std::pair<cityscape::spatial::Point, id_t>;
using rtree_index = bgi::rtree<rtree_leaf_point, bgi::rstar<4, 2>>;

//! Spatial index class
//! \brief Base class of a spatial index (point)
class SpatialIndex {
 public:
  //! Default constructor, construct index value by value
  SpatialIndex() = default;

  //! Construct spatial index through packing algorithm
  explicit SpatialIndex(const std::vector<rtree_leaf_point>& values);

  //! Insert a point
  void insert(const rtree_leaf_point& leaf);

  //! K nearest neighbor query
  //! \param[in] query_point point need to be queried
  //! \param[in] k number of nearest neighbor
  //! \param[out] query_result knn query result
  std::vector<rtree_leaf_point> knn(
      const cityscape::spatial::Point& query_point, unsigned k);

  //! size of the index
  id_t size() const { return indexer_.size(); }

 private:
  //! rtree for spatial index
  rtree_index indexer_;
};
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_INDEX_H_
