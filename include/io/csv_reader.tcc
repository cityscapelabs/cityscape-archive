#ifndef CITYSCAPE_CSV_READER_TCC
#define CITYSCAPE_CSV_READER_TCC

template <typename Col_type>
std::vector<Col_type> cityscape::io::CSV_reader::get_col(
    const std::string& key) {
  auto idx = header_map_.at(key);
  return col_data_.at(idx);
}

template <>
inline std::vector<double> cityscape::io::CSV_reader::get_col<double>(
    const std::string& key) {
  auto idx = header_map_.at(key);
  auto string_vec = col_data_.at(idx);

  std::vector<double> double_vec(string_vec.size());
  std::transform(string_vec.begin(), string_vec.end(), double_vec.begin(),
                 [](std::string const& val) { return std::stod(val); });
  return double_vec;
}

template <>
inline std::vector<int> cityscape::io::CSV_reader::get_col<int>(
    const std::string& key) {
  auto idx = header_map_.at(key);
  auto string_vec = col_data_.at(idx);

  std::vector<int> int_vec(string_vec.size());
  std::transform(string_vec.begin(), string_vec.end(), int_vec.begin(),
                 [](std::string const& val) { return std::stoi(val); });
  return int_vec;
}

#endif  // CITYSCAPE_CSV_READER_TCC
