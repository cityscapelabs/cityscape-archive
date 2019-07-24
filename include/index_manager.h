#ifndef CITYSCAPE_INDEX_H_
#define CITYSCAPE_INDEX_H_

#include <limits>
#include <mutex>

#include "types.h"

namespace cityscape {
//! Graph index class
//! \brief Base class of a graph index (vertex)
class IndexManager {
 public:
  //! Constructor with an inital value for index
  explicit IndexManager(cityscape::id_t idx = 0);

  //! Current index
  cityscape::id_t current_index() const;

  //! Max value
  cityscape::id_t max() const;

  //! Create index
  cityscape::id_t create_index();

 private:
  //! index
  cityscape::id_t index_{0};
  //! Initial value
  cityscape::id_t init_{0};
  //! Mutex
  std::mutex index_mutex_;
};
}  // namespace cityscape

#endif  // CITYSCAPE_INDEX_H_
