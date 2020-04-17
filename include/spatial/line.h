#ifndef CITYSCAPE_LINE_H
#define CITYSCAPE_LINE_H

#include <vector>

#include "edge.h"
#include "point.h"

namespace cityscape {
namespace spatial {
//! Spatial line class
//! \brief Base class of a spatial line
class Line : public cityscape::graph::Edge {
 public:
  //! Constructor with source and destination nodes and a unique edge id
  //! \param[in] src Source node pointer
  //! \param[in] dest Destination node pointer
  //! \param[in] id Index of the edge
  //! \param[in] tag Tag to categorize edge (default is empty)
  Line(const std::shared_ptr<cityscape::spatial::Point>& src,
       const std::shared_ptr<cityscape::spatial::Point>& dest,
       cityscape::id_t id, const std::string& tag = std::string());

  //! Source point
  std::shared_ptr<const cityscape::spatial::Point> src() const { return src_; }

  //! Destination point
  std::shared_ptr<const cityscape::spatial::Point> dest() const {
    return dest_;
  }

  //! Points vector (for boost usage)
  std::vector<cityscape::spatial::Point*> points() const { return points_; };
  //  std::vector<cityscape::spatial::Point*> points;

 protected:
  //! Point id
  using cityscape::graph::Edge::id_;
  //! Tags
  using cityscape::graph::Edge::tags_;
  //! Weight
  using cityscape::graph::Edge::weight_;

 private:
  //! Source node
  std::shared_ptr<const cityscape::spatial::Point> src_;
  //! Destination node
  std::shared_ptr<const cityscape::spatial::Point> dest_;
  //! points vector (for boost usage)
  std::vector<cityscape::spatial::Point*> points_;
};
}  // namespace spatial
}  // namespace cityscape

// Register Line into boost
#include "line_register.h"

#endif  // CITYSCAPE_LINE_H
