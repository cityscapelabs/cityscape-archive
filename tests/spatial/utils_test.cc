#include "catch.hpp"
#include "spatial_index.h"
#include "utils_compare.h"
#include <chrono>
#include <segment.h>
// Check Spatial point class
TEST_CASE("Spatial utills check", "[spatial][utils]") {
  using Point = cityscape::spatial::Point2d;
  using Seg = cityscape::spatial::Segment<Point>;

  const std::array<double, 2> coordinates0 = {1.5, 2.4};
  const std::array<double, 2> coordinates1 = {1.8, 2.4};
  const std::array<double, 2> coordinates2 = {3, 4};

  // create some source points
  auto p0 = std::make_shared<Point>(0, "spatial0", coordinates0, "school0");
  auto p1 = std::make_shared<Point>(1, "spatial1", coordinates1, "school1");
  auto p2 = std::make_shared<Point>(2, "spatial2", coordinates2, "school2");
  const std::vector<std::shared_ptr<Point>> src_points{p0, p1, p2};

  // create some dst points
  std::vector<std::shared_ptr<Point>> dst_points{
      std::make_shared<Point>(Point(0, "spatial2", {3.1, 3.9}, "residential0")),
      std::make_shared<Point>(Point(1, "spatial1", {1.3, 2.3}, "residential1")),
      std::make_shared<Point>(
          Point(2, "spatial1", {1.75, 2.5}, "residential2"))};

  // create some segments
  auto seg0 = std::make_shared<Seg>(p0, p1, 0, "seg0");
  auto seg1 = std::make_shared<Seg>(p0, p2, 1, "seg1");
  auto seg2 = std::make_shared<Seg>(p1, p2, 2, "seg2");
  const std::vector<std::shared_ptr<Seg>> segments{seg0, seg1, seg2};

  SECTION("Map two points list") {
    auto map = cityscape::spatial::map_closest_objects(src_points, dst_points);
    REQUIRE(map[src_points[0]]->id() == 1);
    REQUIRE(map[src_points[1]]->id() == 2);
    REQUIRE(map[src_points[2]]->id() == 0);
  }

  SECTION("Map points to segment") {
    auto map = cityscape::spatial::map_closest_objects(dst_points, segments);
    REQUIRE(map[dst_points[0]]->id() == 2);
    REQUIRE(map[dst_points[1]]->id() == 0);
  }

  SECTION("Merge two points") {
    cityscape::spatial::merge_object_pair(src_points[0], dst_points[0]);
    REQUIRE(dst_points[0]->check_tag("school0") == true);
  }

  SECTION("Merge two vectors of points based on distance") {
    auto dist_cond = cityscape::spatial::Distance_condition<Point>(0.15);

    auto leftovers =
        cityscape::spatial::merge_objects(src_points, dst_points, dist_cond);
    REQUIRE(leftovers.size() == 1);
    REQUIRE(dst_points[0]->check_tag("school2") == true);
    REQUIRE(dst_points[1]->check_tag("school0") == false);
    REQUIRE(dst_points[2]->check_tag("school1") == true);
  }

  SECTION("Merge two vectors of points based on name") {
    auto name_cond = cityscape::spatial::Name_condition<Point>();

    auto leftovers =
        cityscape::spatial::merge_objects(src_points, dst_points, name_cond);
    REQUIRE(leftovers.size() == 1);
    REQUIRE(dst_points[0]->check_tag("school2") == true);
    REQUIRE(dst_points[1]->check_tag("school0") == false);
    REQUIRE(dst_points[2]->check_tag("school1") == true);
  }

  SECTION("Merge two vectors of points based on name") {
    auto name_cond = cityscape::spatial::Name_condition<Point>();
    auto dist_cond = cityscape::spatial::Distance_condition<Point>(0.15);

    auto leftovers = cityscape::spatial::merge_objects(src_points, dst_points,
                                                       name_cond && dist_cond);
    REQUIRE(leftovers.size() == 1);
    REQUIRE(dst_points[0]->check_tag("school2") == true);
    REQUIRE(dst_points[1]->check_tag("school0") == false);
    REQUIRE(dst_points[2]->check_tag("school1") == true);
  }
  //
}
