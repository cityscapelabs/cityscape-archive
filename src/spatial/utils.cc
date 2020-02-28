#include "utils.h"

std::map<std::shared_ptr<cityscape::spatial::Point>,
         std::shared_ptr<cityscape::spatial::Point>>
    cityscape::spatial::map_points(
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

void cityscape::spatial::merge_point_pair(
    const std::shared_ptr<cityscape::spatial::Point>& src_ptr,
    std::shared_ptr<cityscape::spatial::Point>& dst_ptr) {
  auto src_tags = src_ptr->tag();
  for (const auto& src_tag : src_tags) {
    dst_ptr->add_tag(src_tag);
  }
}

std::vector<std::shared_ptr<cityscape::spatial::Point>>
    cityscape::spatial::merge_points(
        const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
            src_points,
        std::vector<std::shared_ptr<cityscape::spatial::Point>>& dst_points,
        double dist_thre) {
  std::vector<std::shared_ptr<cityscape::spatial::Point>> leftovers;
  auto relation_map = map_points(src_points, dst_points);
  for (const auto& src_p : src_points) {
    auto dst_p = relation_map.at(src_p);
    auto dist = boost::geometry::distance(*src_p, *dst_p);
    if (dist < dist_thre) {
      merge_point_pair(src_p, dst_p);
    } else {
      leftovers.emplace_back(src_p);
    }
  }
  return leftovers;
}
std::vector<std::shared_ptr<cityscape::spatial::Point>>
    cityscape::spatial::construct_points_csv(
        const cityscape::spatial::CSV_point_info& header_info) {

  std::vector<std::shared_ptr<cityscape::spatial::Point>> point_list;
  io::CSVReader<5> in(header_info.path);
  in.read_header(io::ignore_extra_column, header_info.id, header_info.x,
                 header_info.y, header_info.name, header_info.tag);
  id_t pid;
  double x, y;
  std::string name, tag;
  while (in.read_row(pid, x, y, name, tag)) {
    // Coordinates
    std::array<double, 2> coordinates = {x, y};
    // point construction
    auto p = std::make_shared<cityscape::spatial::Point>(pid, name, coordinates,
                                                         tag);
    point_list.emplace_back(p);
  }
  return point_list;
}
