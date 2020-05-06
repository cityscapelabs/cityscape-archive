#include "utils_io.h"

std::vector<std::shared_ptr<cityscape::spatial::Point2d>>
    cityscape::io::construct_points_csv(
        const cityscape::io::CSV_point_info& header_info) {

  std::vector<std::shared_ptr<cityscape::spatial::Point2d>> point_list;
  ::io::CSVReader<5> in(header_info.path);
  in.read_header(::io::ignore_extra_column, header_info.id, header_info.x,
                 header_info.y, header_info.name, header_info.tag);
  id_t pid;
  double x, y;
  std::string name, tag;
  while (in.read_row(pid, x, y, name, tag)) {
    // Coordinates
    std::array<double, 2> coordinates = {x, y};
    // point construction
    auto p = std::make_shared<cityscape::spatial::Point2d>(pid, name,
                                                           coordinates, tag);
    point_list.emplace_back(p);
  }
  return point_list;
}
