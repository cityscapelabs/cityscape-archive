#ifndef CITYSCAPE_SPATIAL_INDEX_TCC
#define CITYSCAPE_SPATIAL_INDEX_TCC

template <typename Leaf>
cityscape::spatial::SpatialIndex<Leaf>::SpatialIndex(
    const std::vector<Leaf>& values) {
  bgi::rtree<Leaf, bgi::rstar<4, 2>> rtree(values);
  indexer_ = rtree;
}

template <typename Leaf>
void cityscape::spatial::SpatialIndex<Leaf>::insert(const Leaf& leaf) {
  indexer_.insert(leaf);
}

template <typename Leaf>
std::vector<Leaf> cityscape::spatial::SpatialIndex<Leaf>::knn(
    const cityscape::spatial::Point& query_point, unsigned k) {

  std::vector<Leaf> query_result;
  indexer_.query(bgi::nearest(query_point, k),
                 std::back_inserter(query_result));

  return query_result;
}

#endif