#ifndef CITYSCAPE_CSV_READER_H
#define CITYSCAPE_CSV_READER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace cityscape {
namespace io {
//! CSV_reader class
//! \brief Base class to read csv file
class CSV_reader {
 public:
  //! Construct with filepath
  //! \param[in] filepath csv file path
  explicit CSV_reader(const std::string& filepath);

  //! Get headers for csv file
  const std::vector<std::string>& headers() const { return headers_; }
  //! Get row data for csv file
  const std::vector<std::vector<std::string>>& row_data() const {
    return row_data_;
  }
  //! Get col data for csv file
  const std::vector<std::vector<std::string>>& col_data() const {
    return col_data_;
  }
  //! Get column
  //! \param[in] key name of the column
  template <typename Col_type>
  inline std::vector<Col_type> get_col(const std::string& key);

 private:
  //! Read csv data in row fomat
  void read_row_data();
  //! Helper function to read one row from csv file
  bool read_row(std::istream& str);
  //! Transfer row format data to col format data
  void row_to_col();
  //! Construct header map
  void header_map();

  //! Filepath
  std::string filepath_;
  //! CSV row buffer
  std::vector<std::string> row_;
  //! CSV headers
  std::vector<std::string> headers_;
  //! CSV header map
  std::map<std::string, std::size_t> header_map_;
  //! CSV data in row format
  std::vector<std::vector<std::string>> row_data_;
  //! CSV data in column format
  std::vector<std::vector<std::string>> col_data_;
};

#include "csv_reader.tcc"
}  // namespace io
}  // namespace cityscape

#endif  // CITYSCAPE_CSV_READER_H
