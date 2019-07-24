#include "index_manager.h"
//! Constructor with an inital value for index
cityscape::IndexManager::IndexManager(cityscape::id_t idx)
    : index_{idx}, init_{idx} {};

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
  return ++index_;
}
