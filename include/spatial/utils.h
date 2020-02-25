#ifndef CITYSCAPE_UTILS_H
#define CITYSCAPE_UTILS_H

#include "spatial_index.h"
#include <map>

namespace cityscape {
namespace spatial {

//! Map one list of points to another list of points based on nearest neighbor
//! \param[in] src_points points to map from (source points)
//! \param[in] dst_points points to map to (dest points)
//! \param[out] relation_map mapping relationship for input point lists. Keys
//! are dest points
std::map<std::shared_ptr<cityscape::spatial::Point>,
         std::shared_ptr<cityscape::spatial::Point>>
    map_points(const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
                   src_points,
               const std::vector<std::shared_ptr<cityscape::spatial::Point>>&
                   dst_points);

//! Merge one point to another point
//! \param[in] src_ptr point ptr to merge from (source points)
//! \param[in] src_ptr point ptr to merge to (dest points)
void merge_point_pair(const std::shared_ptr<cityscape::spatial::Point>& src_ptr,
                      std::shared_ptr<cityscape::spatial::Point>& dst_ptr);

//! Merge one list of points to another list of points based on nearest neighbor
//! \param[in] src_points points to merge from (source points)
//! \param[in] dst_points points to merge to (dest points)
//! \param[in] dist_thre min distance to merge
//! \param[out] leftover leftover points that do not satisfy merging
//! requirements
std::vector<std::shared_ptr<cityscape::spatial::Point>> merge_points(
    const std::vector<std::shared_ptr<cityscape::spatial::Point>>& src_points,
    std::vector<std::shared_ptr<cityscape::spatial::Point>>& dst_points,
    double dist_thre);
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_H
