#include "io/csv_reader.h"

cityscape::io::CSV_reader::CSV_reader(const std::string& filepath) {
  filepath_ = filepath;
  read_row_data();
  row_to_col();
}

bool cityscape::io::CSV_reader::read_row(std::istream& str) {
  std::string line;
  std::getline(str, line);
  std::stringstream lineStream(line);
  std::string cell;

  row_.clear();
  while (std::getline(lineStream, cell, ',')) {
    row_.push_back(cell);
  }
  //  // This checks for a trailing comma with no data after it.
  //  if (!lineStream && cell.empty()) {
  //    // If there was a trailing comma then add an empty element.
  //    row_.emplace_back("");
  //  }
  return !row_.empty();
}

void cityscape::io::CSV_reader::header_map() {
  std::size_t n_key = headers_.size();
  for (std::size_t i = 0; i < n_key; i++) {
    header_map_[headers_[i]] = i;
  }
}

void cityscape::io::CSV_reader::read_row_data() {
  std::ifstream infile(filepath_);
  read_row(infile);
  headers_ = row_;
  header_map();
  while (read_row(infile)) {
    row_data_.emplace_back(row_);
  }
}

void cityscape::io::CSV_reader::row_to_col() {
  std::size_t n_col = headers_.size();
  std::size_t n_row = row_data_.size();

  for (std::size_t i = 0; i < n_col; i++) {
    std::vector<std::string> col;
    col_data_.emplace_back(col);
  }

  for (std::size_t i = 0; i < n_row; i++) {
    auto row = row_data_.at(i);
    for (std::size_t j = 0; j < n_col; j++) {
      col_data_[j].emplace_back(row[j]);
    }
  }
}

// std::vector<double> cityscape::IO::CSV_reader::get_col(const std::string&
// key){
//  auto idx = header_map_.at(key);
//  auto string_vec =  col_data_.at(idx);
//
//  std::vector<double> double_vec(string_vec.size());
//  std::transform(string_vec.begin(), string_vec.end(), double_vec.begin(),
//                 [](std::string const& val) {return std::stod(val);});
//  return double_vec;
//}
