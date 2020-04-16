#ifndef CITYSCAPE_LINE_REGISTER_H
#define CITYSCAPE_LINE_REGISTER_H

#include "line.h"
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/range.hpp>

// Adaption of line for boost geometry lib

using QLineString = cityscape::spatial::Line;
using QPoint = cityscape::spatial::Point;
namespace boost {
template <>
struct range_iterator<QLineString> {
  typedef std::vector<QPoint*>::iterator type;
};

template <>
struct range_const_iterator<QLineString> {
  typedef std::vector<QPoint*>::const_iterator type;
};
}  // namespace boost

namespace cityscape {
namespace spatial {
inline std::vector<QPoint*>::iterator range_begin(QLineString& qls) {
  return qls.points().begin();
}

inline std::vector<QPoint*>::iterator range_end(QLineString& qls) {
  return qls.points().end();
}

inline std::vector<QPoint*>::const_iterator range_begin(
    const QLineString& qls) {
  return qls.points().begin();
}

inline std::vector<QPoint*>::const_iterator range_end(const QLineString& qls) {
  return qls.points().end();
}
}  // namespace spatial
}  // namespace cityscape

BOOST_GEOMETRY_REGISTER_LINESTRING(QLineString);

#endif  // CITYSCAPE_LINE_REGISTER_H
