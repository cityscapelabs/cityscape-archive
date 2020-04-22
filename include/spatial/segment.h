#ifndef CITYSCAPE_SEGMENT_H
#define CITYSCAPE_SEGMENT_H

#include <vector>

#include "edge.h"
#include "point.h"
#include "point_2d.h"

namespace cityscape {
namespace spatial {
//! Spatial line class
//! \brief Base class of a spatial line
class Segment : public cityscape::graph::Edge {
 public:
  //! Constructor with source and destination nodes and a unique edge id
  //! \param[in] src Source node pointer
  //! \param[in] dest Destination node pointer
  //! \param[in] id Index of the edge
  //! \param[in] tag Tag to categorize edge (default is empty)
  Segment(const std::shared_ptr<cityscape::spatial::Point_2d>& src,
          const std::shared_ptr<cityscape::spatial::Point_2d>& dest,
          cityscape::id_t id, const std::string& tag = std::string())
      : Edge(src, dest, id, tag), src_{src}, dest_{dest} {};

  //! Source point
  std::shared_ptr<const cityscape::spatial::Point_2d> src() const {
    return src_;
  }

  //! Destination point
  std::shared_ptr<const cityscape::spatial::Point_2d> dest() const {
    return dest_;
  }

 protected:
  //! Point id
  using cityscape::graph::Edge::id_;
  //! Tags
  using cityscape::graph::Edge::tags_;
  //! Weight
  using cityscape::graph::Edge::weight_;

 private:
  //! Source node
  std::shared_ptr<cityscape::spatial::Point_2d> src_;
  //! Destination node
  std::shared_ptr<cityscape::spatial::Point_2d> dest_;
};
}  // namespace spatial
}  // namespace cityscape

// Register segment into boost

namespace boost {
namespace geometry {
namespace traits {
using Seg = cityscape::spatial::Segment;
using Point = cityscape::spatial::Point_2d;
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

#endif  // CITYSCAPE_SEGMENT_H
