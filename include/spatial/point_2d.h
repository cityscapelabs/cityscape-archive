#ifndef CITYSCAPE_POINT_2D_H
#define CITYSCAPE_POINT_2D_H
#include "point.h"
#include <boost/geometry/geometries/register/point.hpp>

namespace cityscape {
namespace spatial {
//! Spatial 2D point class
//! \brief class of a 2D spatial point (vertex) in cartesian coordinate system
class Point2d : public cityscape::spatial::Point<2> {
 public:
  Point2d() = default;

  Point2d(cityscape::id_t id, const std::string& name,
          std::array<double, 2> coordinates,
          const std::string& tag = std::string())
      : Point<2>(id, name, coordinates, tag){};

  //! Return x coordinates
  //! \retval x coordinate of the point
  double get_x() const { return this->template get<0>(); }
  //! Return y coordinates
  //! \retval y coordinate of the point
  double get_y() const { return this->template get<1>(); }

  //! Set coordinate x
  void set_x(double x) { this->template set<0>(x); };
  //! Set coordinate y
  void set_y(double y) { this->template set<1>(y); };
};
}  // namespace spatial
}  // namespace cityscape
// Register Point as a 2D Point
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(cityscape::spatial::Point2d, double,
                                         cs::cartesian, get_x, get_y, set_x,
                                         set_y)
#endif  // CITYSCAPE_POINT_2D_H
