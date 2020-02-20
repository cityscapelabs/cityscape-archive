#include "utils.h"

std::map<std::shared_ptr<cityscape::spatial::Point>,
         std::shared_ptr<cityscape::spatial::Point>>
    cityscape::spatial::merge_points(
        const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
            src_points,
        const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
            dst_points) {

  std::map<std::shared_ptr<cityscape::spatial::Point>,
           std::shared_ptr<cityscape::spatial::Point>>
      relation_map;

  // construct spatial index using dst points
  cityscape::spatial::SpatialIndex<std::shared_ptr<cityscape::spatial::Point>>
      index(dst_points);

  for (const auto& query_p : src_points) {
    auto q_result = index.knn(*query_p, 1);
    auto closet_p = q_result.at(0);
    relation_map[query_p] = closet_p;
  }
  return relation_map;
}
