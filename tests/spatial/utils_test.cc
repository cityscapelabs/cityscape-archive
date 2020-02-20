#include "catch.hpp"
#include "spatial_index.h"
#include "utils.h"
#include <chrono>
// Check Spatial point class
TEST_CASE("Spatial utills check", "[spatial][utils]") {
  typedef cityscape::spatial::Point Point;

  // create some source points
  const std::vector<std::shared_ptr<Point>> src_points{
      std::make_shared<Point>(Point(0, "spatial0", {1.5, 2.4})),
      std::make_shared<Point>(Point(1, "spatial1", {1.8, 2.4})),
      std::make_shared<Point>(Point(2, "spatial2", {3, 4}))};

  // create some dst points
  const std::vector<std::shared_ptr<Point>> dst_points{
      std::make_shared<Point>(Point(0, "spatial0", {3.1, 4})),
      std::make_shared<Point>(Point(1, "spatial1", {1.3, 2.4})),
      std::make_shared<Point>(Point(2, "spatial2", {1.75, 2.5}))};

  SECTION("Merging two points list") {
    auto map = cityscape::spatial::merge_points(src_points, dst_points);
    REQUIRE(map[src_points[0]]->id() == 1);
    REQUIRE(map[src_points[1]]->id() == 2);
    REQUIRE(map[src_points[2]]->id() == 0);
  }
}
