#ifndef CITYSCAPE_SPATIAL_POINT_H_
#define CITYSCAPE_SPATIAL_POINT_H_

#include <boost/geometry/geometry.hpp>

#include <array>
#include <limits>
#include <memory>
#include <set>
#include <vector>

#include "node.h"
#include "types.h"

namespace cityscape {
namespace spatial {
template <std::size_t Dim,
          typename CoordinateSystem = boost::geometry::cs::cartesian>
//! Spatial point class
//! \brief Base class of a spatial point (vertex)
class Point : public cityscape::graph::Node {
 public:
  /// \constructor_default_no_init
  Point() = default;
  //! Constructor with unique point id
  //! \param[in] id Index of the edge
  //! \param[in] name Unique name of the point
  //! \param[in] tag Tag to categorize point (default is empty)
  //! \param[in] coords Coordinates of the point (default is empty)
  Point(cityscape::id_t id, const std::string& name,
        std::array<double, Dim> coordinates,
        const std::string& tag = std::string())
      : cityscape::graph::Node(id, name, tag), coordinates_(coordinates){};

  //! Return kth coordinates
  //! \retval kth coordinate of the point
  template <std::size_t K>
  double get() const {
    if (K > Dim - 1) {
      throw std::runtime_error("Try to get more dimension for a point");
    }
    return coordinates_[K];
  }

  //! Set kth coordinate
  template <std::size_t K>
  void set(double y) {
    if (K > Dim - 1) {
      throw std::runtime_error("Try to get more dimension for a point");
    }
    coordinates_[K] = y;
  }

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
  std::array<double, Dim> coordinates_;
};

}  // namespace spatial
}  // namespace cityscape

// Register Point as a 2D Point
// Adapt the point to the boost concept
namespace boost {
namespace geometry {
namespace traits {
template <std::size_t DimensionCount, typename CoordinateSystem>
struct tag<cityscape::spatial::Point<DimensionCount, CoordinateSystem>> {
  typedef point_tag type;
};

template <std::size_t DimensionCount, typename CoordinateSystem>
struct coordinate_type<
    cityscape::spatial::Point<DimensionCount, CoordinateSystem>> {
  typedef double type;
};

template <std::size_t DimensionCount, typename CoordinateSystem>
struct coordinate_system<
    cityscape::spatial::Point<DimensionCount, CoordinateSystem>> {
  typedef cs::cartesian type;
};

template <std::size_t DimensionCount, typename CoordinateSystem>
struct dimension<cityscape::spatial::Point<DimensionCount, CoordinateSystem>>
    : boost::mpl::int_<DimensionCount> {};

template <std::size_t DimensionCount, typename CoordinateSystem,
          std::size_t Dimension>
struct access<cityscape::spatial::Point<DimensionCount, CoordinateSystem>,
              Dimension> {
  static inline double get(
      cityscape::spatial::Point<DimensionCount, CoordinateSystem> const& p) {
    return p.template get<Dimension>();
  }

  static inline void set(
      cityscape::spatial::Point<DimensionCount, CoordinateSystem> const& p,
      double const& value) {
    p.template set<Dimension>(value);
  }
};
}  // namespace traits
}  // namespace geometry
}  // namespace boost
#endif  // CITYSCAPE_SPATIAL_POINT_H_
