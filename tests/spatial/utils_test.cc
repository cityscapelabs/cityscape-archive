#include "catch.hpp"
#include "spatial_index.h"
#include "utils.h"
#include <chrono>
// Check Spatial point class
TEST_CASE("Spatial utills check", "[spatial][utils]") {
  typedef cityscape::spatial::Point Point;

  // create some source points
  const std::vector<std::shared_ptr<Point>> src_points{
      std::make_shared<Point>(Point(0, "spatial0", {1.5, 2.4}, "school0")),
      std::make_shared<Point>(Point(1, "spatial1", {1.8, 2.4}, "school1")),
      std::make_shared<Point>(Point(2, "spatial2", {3, 4}, "school2"))};

  // create some dst points
  std::vector<std::shared_ptr<Point>> dst_points{
      std::make_shared<Point>(Point(0, "spatial0", {3.1, 4}, "residential0")),
      std::make_shared<Point>(Point(1, "spatial1", {1.3, 2.4}, "residential1")),
      std::make_shared<Point>(
          Point(2, "spatial2", {1.75, 2.5}, "residential2"))};

  SECTION("Map two points list") {
    auto map = cityscape::spatial::map_points(src_points, dst_points);
    REQUIRE(map[src_points[0]]->id() == 1);
    REQUIRE(map[src_points[1]]->id() == 2);
    REQUIRE(map[src_points[2]]->id() == 0);
  }

  SECTION("Merge two points") {
    cityscape::spatial::merge_point_pair(src_points[0], dst_points[0]);
    REQUIRE(dst_points[0]->check_tag("school0") == true);
  }

  SECTION("Merge two vectors of points") {
    double thre = 0.15;
    auto leftovers =
        cityscape::spatial::merge_points(src_points, dst_points, thre);
    REQUIRE(leftovers.size() == 1);
    REQUIRE(dst_points[0]->check_tag("school2") == true);
    REQUIRE(dst_points[1]->check_tag("school0") == false);
    REQUIRE(dst_points[2]->check_tag("school1") == true);
  }
}
