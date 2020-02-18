#include "point.h"

//! Constructor with unique node id, name, coordinates and tag
cityscape::spatial::Point::Point(cityscape::id_t id, const std::string& name,
                                 std::array<double, 2> coordinates,
                                 const std::string& tag)
    : cityscape::graph::Node(id, name, tag) {
  coordinates_ = coordinates;
}

//! Return coordinate x of the point
double cityscape::spatial::Point::get_x() const { return coordinates_.at(0); }

//! Return coordinate y of the point
double cityscape::spatial::Point::get_y() const { return coordinates_.at(1); }

//! Set coordinate x
void cityscape::spatial::Point::set_x(double x) { coordinates_[0] = x; }

//! Set coordinate y
void cityscape::spatial::Point::set_y(double y) { coordinates_[1] = y; }