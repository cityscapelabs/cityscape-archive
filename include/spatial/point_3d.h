#ifndef CITYSCAPE_POINT_3D_H
#define CITYSCAPE_POINT_3D_H
#include "point.h"
#include <boost/geometry/geometries/register/point.hpp>

namespace cityscape {
namespace spatial {
//! Spatial 3D point class
//! \brief class of a 3D spatial point (vertex) in cartesian coordinate system
class Point3d : public cityscape::spatial::Point<3> {
 public:
  Point3d() = default;

  Point3d(cityscape::id_t id, const std::string& name,
          std::array<double, 3> coordinates,
          const std::string& tag = std::string())
      : Point<3>(id, name, coordinates, tag){};

  //! Return x coordinates
  //! \retval x coordinate of the point
  double get_x() const { return this->template get<0>(); }
  //! Return y coordinates
  //! \retval y coordinate of the point
  double get_y() const { return this->template get<1>(); }
  //! Return z coordinates
  //! \retval z coordinate of the point
  double get_z() const { return this->template get<2>(); }

  //! Set coordinate x
  void set_x(double x) { this->template set<0>(x); };
  //! Set coordinate y
  void set_y(double y) { this->template set<1>(y); };
  //! Set coordinate z
  void set_z(double z) { this->template set<2>(z); };
};
}  // namespace spatial
}  // namespace cityscape
// Register Point as a 2D Point
BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(cityscape::spatial::Point3d, double,
                                         cs::cartesian, get_x, get_y, get_z,
                                         set_x, set_y, set_z)
#endif  // CITYSCAPE_POINT_3D_H
