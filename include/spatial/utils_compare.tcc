#ifndef CITYSCAPE_UTILS_TCC
#define CITYSCAPE_UTILS_TCC

#include "utils_compare.h"

template <typename Src, typename Dst>
std::map<std::shared_ptr<Src>, std::shared_ptr<Dst>> map_closest_objects(
    const std::vector<std::shared_ptr<Src>>& src_objs,
    const std::vector<std::shared_ptr<Dst>>& dst_objs) {

  std::map<std::shared_ptr<Src>, std::shared_ptr<Dst>> relation_map;

  // construct spatial index using dst objects
  cityscape::spatial::SpatialIndex<std::shared_ptr<Dst>> index(dst_objs);

  for (const auto& query_p : src_objs) {
    auto q_result = index.knn(*query_p, 1);
    auto closet_p = q_result.at(0);
    relation_map[query_p] = closet_p;
  }
  return relation_map;
};

template <typename Obj>
void merge_object_pair(const std::shared_ptr<Obj>& src_obj,
                       std::shared_ptr<Obj>& dst_obj) {
  auto src_tags = src_obj->tag();
  for (const auto& src_tag : src_tags) {
    dst_obj->add_tag(src_tag);
  }
}

template <typename Obj>
std::vector<std::shared_ptr<Obj>> merge_objects(
    const std::vector<std::shared_ptr<Obj>>& src_objects,
    std::vector<std::shared_ptr<Obj>>& dst_objects,
    const Condition<Obj>& cond) {

  std::vector<std::shared_ptr<Obj>> leftovers;
  auto relation_map = map_closest_objects(src_objects, dst_objects);
  for (const auto& src_p : src_objects) {
    auto dst_p = relation_map.at(src_p);
    if (cond.is_satisfied(*src_p, *dst_p)) {
      merge_object_pair(src_p, dst_p);
    } else {
      leftovers.emplace_back(src_p);
    }
  }
  return leftovers;
}

#endif  // CITYSCAPE_UTILS_TCC