#ifndef CITYSCAPE_SEGMENT_H
#define CITYSCAPE_SEGMENT_H

#include <vector>

#include "edge.h"
#include "point.h"
#include "point_2d.h"

namespace cityscape {
namespace spatial {
template <typename P>
//! Spatial Segment class
//! \brief Base class of a spatial segment
class Segment : public cityscape::graph::Edge {
 public:
  //! Constructor with source and destination nodes and a unique edge id
  //! \param[in] src Source node pointer
  //! \param[in] dest Destination node pointer
  //! \param[in] id Index of the edge
  //! \param[in] tag Tag to categorize edge (default is empty)
  Segment(const std::shared_ptr<P>& src, const std::shared_ptr<P>& dest,
          cityscape::id_t id, const std::string& tag = std::string())
      : Edge(src, dest, id, tag), src_{src}, dest_{dest} {};

  //! Source point
  std::shared_ptr<const P> src() const { return src_; }

  //! Destination point
  std::shared_ptr<const P> dest() const { return dest_; }

 private:
  //! Source node
  std::shared_ptr<P> src_;
  //! Destination node
  std::shared_ptr<P> dest_;
};
}  // namespace spatial
}  // namespace cityscape

// Register segment into boost

namespace boost {
namespace geometry {
namespace traits {
using namespace cityscape::spatial;
template <typename P>
struct tag<Segment<P>> {
  typedef segment_tag type;
};

template <typename P>
struct point_type<Segment<P>> {
  typedef P type;
};

template <std::size_t Dimension, typename P>
struct indexed_access<Segment<P>, 0, Dimension> {
  typedef typename geometry::coordinate_type<P>::type coordinate_type;

  static inline coordinate_type get(Segment<P> const& s) {
    return geometry::get<Dimension>(*s.src());
  }

  static inline void set(Segment<P>& s, coordinate_type const& value) {
    geometry::set<Dimension>(*s.src(), value);
  }
};

template <std::size_t Dimension, typename P>
struct indexed_access<Segment<P>, 1, Dimension> {
  typedef typename geometry::coordinate_type<P>::type coordinate_type;

  static inline coordinate_type get(Segment<P> const& s) {
    return geometry::get<Dimension>(*s.dest());
  }

  static inline void set(Segment<P>& s, coordinate_type const& value) {
    geometry::set<Dimension>(*s.dest(), value);
  }
};
}  // namespace traits
}  // namespace geometry
}  // namespace boost

#endif  // CITYSCAPE_SEGMENT_H
