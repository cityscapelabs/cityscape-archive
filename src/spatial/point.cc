#include "point.h"

//! Constructor with unique node id, name, coordinates and tag
cityscape::spatial::Point::Point(cityscape::id_t id, const std::string &name,
                                 std::array<double, 2> coordinates,
                                 const std::string &tag)
    : cityscape::graph::Node(id, name, tag) {
  coordinates_ = coordinates;
  x = coordinates_.at(0);
  y = coordinates_.at(1);
}

//! Return coordinates of the point
std::array<double, 2> cityscape::spatial::Point::coordinates() const {
  return coordinates_;
}
