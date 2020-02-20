#ifndef CITYSCAPE_UTILS_H
#define CITYSCAPE_UTILS_H

#include "spatial_index.h"
#include <map>

namespace cityscape {
namespace spatial {

//! Merge one list of points to another list of points based on nearest neighbor
//! \param[in] src_points points to merge from (source points)
//! \param[in] dst_points points to merge to (dest points)
//! \param[out] merge_map mapping relationship for input point lists. Keys are
//! dest points
std::map<std::shared_ptr<cityscape::spatial::Point>,
         std::shared_ptr<cityscape::spatial::Point>>
    merge_points(const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
                     src_points,
                 const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
                     dst_points);
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_H
