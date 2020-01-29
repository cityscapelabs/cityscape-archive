#ifndef CITYSCAPE_SPATIAL_POINT_H_
#define CITYSCAPE_SPATIAL_POINT_H_

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include <array>
#include <limits>
#include <memory>
#include <set>
#include <vector>

#include "node.h"
#include "types.h"

namespace cityscape {
namespace spatial {

//! Spatial point class
//! \brief Base class of a spatial point (vertex)
class Point : public cityscape::graph::Node {
 public:
  //! Constructor with unique point id
  //! \param[in] id Index of the edge
  //! \param[in] name Unique name of the point
  //! \param[in] tag Tag to categorize point (default is empty)
  //! \param[in] coords Coordinates of the point (default is empty)
  Point(cityscape::id_t id, const std::string& name,
        std::array<double, 2> coordinates,
        const std::string& tag = std::string());

  //! Return x coordinates
  //! \retval x coordinate of the point
  double get_x() const;
  //! Return y coordinates
  //! \retval y coordinate of the point
  double get_y() const;

  //! Set coordinate x
  void set_x(double x);
  //! Set coordinate y
  void set_y(double y);


 protected:
  //! Point id
  using cityscape::graph::Node::id_;
  //! Tags
  using cityscape::graph::Node::tags_;
  //! Name
  using cityscape::graph::Node::name_;
  //! In-edges
  using cityscape::graph::Node::in_edges_;
  //! Out-edges
  using cityscape::graph::Node::out_edges_;

 private:
  std::array<double, 2> coordinates_;
};
}  // namespace spatial
}  // namespace cityscape

// Register Point as a 2D Point
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(cityscape::spatial::Point, double,
                                 cs::cartesian, get_x, get_y, set_x, set_y);

#endif  // CITYSCAPE_SPATIAL_POINT_H_
