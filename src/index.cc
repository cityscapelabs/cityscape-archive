#include "index.h"
//! Constructor with an inital value for index
cityscape::Index::Index(cityscape::id_t idx) : index_{idx} {};

//! Current index
cityscape::id_t cityscape::Index::current_id() const { return index_; }

//! Maximum index value
cityscape::id_t cityscape::Index::max() const {
  return std::numeric_limits<cityscape::id_t>::max();
}

//! Generate id
cityscape::id_t cityscape::Index::create_id() {
  std::lock_guard<std::mutex> guard(id_mutex_);
  ++index_;
  return index_;
}
