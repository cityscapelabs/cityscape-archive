#ifndef CITYSCAPE_INDEX_H_
#define CITYSCAPE_INDEX_H_

#include <limits>
#include <mutex>

#include "types.h"

namespace cityscape {
//! Graph index class
//! \brief Base class of a graph index (vertex)
class Index {
 public:
  //! Constructor with an inital value for index
  explicit Index(cityscape::id_t idx = 0);

  //! Current index
  cityscape::id_t current_id() const;

  //! Max value
  cityscape::id_t max() const;
  
  //! Create id
  cityscape::id_t create_id();

 private:
  //! Index id
  cityscape::id_t index_{0};
  //! Mutex
  std::mutex id_mutex_;
};
}  // namespace cityscape

#endif  // CITYSCAPE_INDEX_H_
