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

  //! Location coordinates for BOOST
  double x;
  double y;

  //! Return coordinates
  //! \retval coordinates_ Coordinates of point
  std::array<double, 2> coordinates() const;

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
BOOST_GEOMETRY_REGISTER_POINT_2D(cityscape::spatial::Point, double,
                                 cs::cartesian, x, y);

#endif  // CITYSCAPE_SPATIAL_POINT_H_
