#include "spatial_index.h"

cityscape::spatial::SpatialIndex::SpatialIndex(
    const std::vector<rtree_leaf_point>& values) {
  rtree_index rtree(values);
  indexer_ = rtree;
}

void cityscape::spatial::SpatialIndex::insert(
    const cityscape::spatial::rtree_leaf_point& leaf) {
  indexer_.insert(leaf);
}

std::vector<cityscape::spatial::rtree_leaf_point>
    cityscape::spatial::SpatialIndex::knn(
        const cityscape::spatial::Point& query_point, unsigned k) {
  std::vector<rtree_leaf_point> query_result;
  indexer_.query(bgi::nearest(query_point, k),
                 std::back_inserter(query_result));

  return query_result;
}
