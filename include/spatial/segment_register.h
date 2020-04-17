#ifndef CITYSCAPE_SEGMENT_REGISTER_H
#define CITYSCAPE_SEGMENT_REGISTER_H

#include "segment.h"
#include <boost/geometry.hpp>

namespace boost {
namespace geometry {
namespace traits {
using Seg = cityscape::spatial::Segment;
using Point = cityscape::spatial::Point;
template <>
struct tag<Seg> {
  typedef segment_tag type;
};

template <>
struct point_type<Seg> {
  typedef Point type;
};

template <std::size_t Dimension>
struct indexed_access<Seg, 0, Dimension> {
  typedef typename geometry::coordinate_type<Point>::type coordinate_type;

  static inline coordinate_type get(Seg const& s) {
    return geometry::get<Dimension>(*s.src());
  }

  static inline void set(Seg& s, coordinate_type const& value) {
    geometry::set<Dimension>(*s.src(), value);
  }
};
template <std::size_t Dimension>
struct indexed_access<Seg, 1, Dimension> {
  typedef typename geometry::coordinate_type<Point>::type coordinate_type;

  static inline coordinate_type get(Seg const& s) {
    return geometry::get<Dimension>(*s.dest());
  }

  static inline void set(Seg& s, coordinate_type const& value) {
    geometry::set<Dimension>(*s.dest(), value);
  }
};

}  // namespace traits
}  // namespace geometry
}  // namespace boost
#endif  // CITYSCAPE_SEGMENT_REGISTER_H