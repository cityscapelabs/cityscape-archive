#ifndef CITYSCAPE_UTILS_H
#define CITYSCAPE_UTILS_H

#include "csv.h"
#include "spatial_index.h"
#include <map>

namespace cityscape {
namespace io {

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

//! Construct a vector of point ptrs from csv file
//! \param[in] csv_info Information of the csv file
//! \param[out] point_list Constructed point ptrs
std::vector<std::shared_ptr<cityscape::spatial::Point2d>> construct_points_csv(
    const CSV_point_info& csv_info);

}  // namespace io
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_H
