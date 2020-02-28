#ifndef CITYSCAPE_UTILS_H
#define CITYSCAPE_UTILS_H

#include "csv.h"
#include "spatial_index.h"
#include <map>

namespace cityscape {
namespace spatial {

//! CSV reader info for point construction
//! \brief CSV reader info for point construction
struct CSV_point_info {
  //! Constructor for info
  //! \param[in] csv_path Path of the csv file
  //! \param[in] x_name Column name for x coordinates
  //! \param[in] y_name Column name for y coordinates
  //! \param[in] point_name Column name for point names
  //! \param[in] point_tag Column name for point tag to categorize node (default
  //! is None)
  CSV_point_info(const std::string& csv_path, const std::string& id_name,
                 const std::string& x_name, const std::string& y_name,
                 const std::string& point_name, const std::string& point_tag)
      : path(csv_path),
        id(id_name),
        x(x_name),
        y(y_name),
        name(point_name),
        tag(point_tag) {}

  std::string path;
  std::string id;
  std::string x;
  std::string y;
  std::string name;
  std::string tag;
};

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

//! Construct a vector of point ptrs from csv file
//! \param[in] csv_info Information of the csv file
//! \param[out] point_list Constructed point ptrs
std::vector<std::shared_ptr<cityscape::spatial::Point>> construct_points_csv(
    const CSV_point_info& csv_info);

}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_H
