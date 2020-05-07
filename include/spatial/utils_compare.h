#ifndef CITYSCAPE_UTILS_COMPARE_H
#define CITYSCAPE_UTILS_COMPARE_H

#include "spatial_index.h"
#include <map>

namespace cityscape {
namespace spatial {
template <typename T>
struct Condition {
  virtual ~Condition() = default;
  virtual bool is_satisfied(T& item1, T& item2) const = 0;
};

template <typename T>
struct Distance_condition : public Condition<T> {
  double max_distance = 0.1;
  Distance_condition(double max_distance) : max_distance(max_distance) {}
  bool is_satisfied(T& item1, T& item2) const {
    return boost::geometry::distance(item1, item2) < max_distance;
  }
};

template <typename T>
struct Name_condition : public Condition<T> {
  bool is_satisfied(T& item1, T& item2) const {
    return item1.name() == item2.name();
  }
};

template <typename T>
struct And_condition : public Condition<T> {
  const Condition<T>& first;
  const Condition<T>& second;
  And_condition(const Condition<T>& first, const Condition<T>& second)
      : first(first), second(second) {}
  bool is_satisfied(T& item1, T& item2) const {
    return first.is_satisfied(item1, item2) &&
           second.is_satisfied(item1, item2);
  }
};
template <typename T>
And_condition<T> operator&&(const Condition<T>& first,
                            const Condition<T>& second) {
  return {first, second};
}

//! Map one list of objects to another list of objects based on nearest neighbor
//! criterial \param[in] src_objs objects to map from (source points) \param[in]
//! dst_objs objects to map to (dest points) \param[out] relation_map mapping
//! relationship for input objects lists. Keys are dest objects
template <typename Src, typename Dst>
std::map<std::shared_ptr<Src>, std::shared_ptr<Dst>> map_closest_objects(
    const std::vector<std::shared_ptr<Src>>& src_objs,
    const std::vector<std::shared_ptr<Dst>>& dst_objs);

//! Merge one object to another point
//! \param[in] src_obj point ptr to merge from (source points)
//! \param[in] dst_obj point ptr to merge to (dest points)
template <typename Obj>
void merge_object_pair(const std::shared_ptr<Obj>& src_obj,
                       std::shared_ptr<Obj>& dst_obj);

//! Merge one list of objects to another list of objects based on nearest
//! neighbor \param[in] src_objects points to merge from (source points)
//! \param[in] dst_objects points to merge to (dest points)
//! \param[in] dist_thre min distance to merge
//! \param[out] leftover leftover points that do not satisfy merging
//! requirements
template <typename Obj>
std::vector<std::shared_ptr<Obj>> merge_objects(
    const std::vector<std::shared_ptr<Obj>>& src_objects,
    std::vector<std::shared_ptr<Obj>>& dst_objects,
    const Condition<std::shared_ptr<Obj>>& cond);

#include "utils_compare.tcc"
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_COMPARE_H
