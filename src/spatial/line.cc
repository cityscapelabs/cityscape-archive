#include "spatial/line.h"

cityscape::spatial::Line::Line(
    const std::shared_ptr<cityscape::spatial::Point>& src,
    const std::shared_ptr<cityscape::spatial::Point>& dest, cityscape::id_t id,
    const std::string& tag)
    : Edge(src, dest, id, tag) {

  src_ = std::const_pointer_cast<const cityscape::spatial::Point>(src);
  dest_ = std::const_pointer_cast<const cityscape::spatial::Point>(dest);

  points.push_back(src.get());
  points.push_back(dest.get());
}
