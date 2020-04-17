#include "catch.hpp"
#include <chrono>

// to store queries results
#include <vector>

#include "segment.h"
#include "spatial_index.h"

// Check Spatial point class
TEST_CASE("Spatial point index", "[spatial][index]") {
  using Point = cityscape::spatial::Point;
  using Seg = cityscape::spatial::Segment;

  const double Tolerance = 1.E-7;
  // create some points for storing
  // Coordinates
  const std::array<double, 2> coordinates0 = {1.5, 2.4};
  const std::array<double, 2> coordinates1 = {1.8, 2.4};
  const std::array<double, 2> coordinates2 = {3, 4};

  auto p0 = std::make_shared<Point>(0, "spatial0", coordinates0);
  auto p1 = std::make_shared<Point>(1, "spatial1", coordinates1);
  auto p2 = std::make_shared<Point>(2, "spatial2", coordinates2);

  const std::vector<std::shared_ptr<Point>> points{p0, p1, p2};
  // create some segments for storing
  auto seg0 = std::make_shared<Seg>(p0, p1, 0, "seg0");
  auto seg1 = std::make_shared<Seg>(p0, p2, 1, "seg1");
  auto seg2 = std::make_shared<Seg>(p1, p2, 2, "seg2");
  const std::vector<std::shared_ptr<Seg>> segments{seg0, seg1, seg2};

  const unsigned n = 3;
  // create a query point
  Point query_p(3, "query point", {1.3, 2.2});

  SECTION("spatial index with no packing ") {
    // create the rtree using default constructor
    auto index = std::make_shared<
        cityscape::spatial::SpatialIndex<std::shared_ptr<Point>>>();

    for (const auto& p : points) {
      index->insert(p);
    }
    REQUIRE(index->size() == n);

    // find nearest values to a point
    auto result_n = index->knn(query_p, 1);
    auto closet_p = result_n.at(0);

    // Test query result id
    REQUIRE(closet_p->id() == 0);
    // Check query result name
    REQUIRE(closet_p->name() == "spatial0");
  }

  SECTION("Index with packing") {
    // create the index using packing algorithm
    auto index = std::make_shared<
        cityscape::spatial::SpatialIndex<std::shared_ptr<Point>>>(points);
    REQUIRE(index->size() == n);

    // find nearest values to a point
    auto result_n = index->knn(query_p, 1);
    auto closet_p = result_n.at(0);

    // Test query result id
    REQUIRE(closet_p->id() == 0);
    // Check query result name
    REQUIRE(closet_p->name() == "spatial0");
  }

  SECTION("Index for segments") {
    // create the index using packing algorithm
    auto index = std::make_shared<
        cityscape::spatial::SpatialIndex<std::shared_ptr<Seg>>>(segments);
    REQUIRE(index->size() == n);

    // find nearest segment to a point
    auto result_n = index->knn(query_p, 1);
    auto closet_seg = result_n.at(0);

    // Test query result id
    REQUIRE(closet_seg->id() == 0);
  }
}
