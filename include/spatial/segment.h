#ifndef CITYSCAPE_SEGMENT_H
#define CITYSCAPE_SEGMENT_H

#include <vector>

#include "edge.h"
#include "point.h"

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
  Segment(const std::shared_ptr<cityscape::spatial::Point>& src,
          const std::shared_ptr<cityscape::spatial::Point>& dest,
          cityscape::id_t id, const std::string& tag = std::string())
      : Edge(src, dest, id, tag), src_{src}, dest_{dest} {};

  //! Source point
  std::shared_ptr<const cityscape::spatial::Point> src() const { return src_; }

  //! Destination point
  std::shared_ptr<const cityscape::spatial::Point> dest() const {
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
  std::shared_ptr<cityscape::spatial::Point> src_;
  //! Destination node
  std::shared_ptr<cityscape::spatial::Point> dest_;
};
}  // namespace spatial
}  // namespace cityscape

// Register segment into boost
#include "segment_register.h"

#endif  // CITYSCAPE_SEGMENT_H
