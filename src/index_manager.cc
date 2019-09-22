#include "index_manager.h"
//! Constructor with an inital value for index
cityscape::IndexManager::IndexManager(cityscape::id_t idx)
    : index_{idx}, next_{idx} {};

//! Current index
cityscape::id_t cityscape::IndexManager::current_index() const {
  return index_;
}

//! Maximum index value
cityscape::id_t cityscape::IndexManager::max() const {
  return std::numeric_limits<cityscape::id_t>::max();
}

//! Generate index
cityscape::id_t cityscape::IndexManager::create_index() {
  std::lock_guard<std::mutex> guard(index_mutex_);
  // Get the next value of index
  // (at init both index and next will be the same)
  index_ = next_;
  // Increment next index by one
  next_ += 1;
  // Return current index
  return index_;
}
