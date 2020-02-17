#include "catch.hpp"

#include <chrono>

// to store queries results
#include <vector>

#include "spatial_index.h"

// Check Spatial point class
TEST_CASE("Spatial point index", "[spatial][point]") {
  typedef cityscape::spatial::Point Point;

  const double Tolerance = 1.E-7;
  // create some points for storing
  const std::vector<Point> points{Point(0, "spatial0", {1.5, 2.4}),
                                  Point(1, "spatial1", {1.8, 2.4}),
                                  Point(2, "spatial2", {3, 4})};
  const unsigned n = 3;
  // create a query point
  Point query_p(3, "query point", {1.3, 2.2});

  SECTION("spatial index with no packing ") {
    // create the rtree using default constructor
    auto index = std::make_shared<cityscape::spatial::SpatialIndex>();

    for (unsigned i = 0; i < n; ++i) {
      auto p = points.at(i);
      // insert new value
      index->insert(std::make_pair(p, i));
    }

    REQUIRE(index->size() == n);

    // find nearest values to a point
    auto result_n = index->knn(query_p, 1);
    auto closet_p = result_n.at(0).first;

    // Test query result id
    REQUIRE(closet_p.id() == 0);
    // Check query result name
    REQUIRE(closet_p.name() == "spatial0");
  }

  SECTION("Index with packing") {
    std::vector<cityscape::spatial::rtree_leaf_point> leaves;
    // create some values
    for (unsigned i = 0; i < n; ++i) {
      auto p = points.at(i);
      // insert new value
      leaves.emplace_back(std::make_pair(p, i));
    }
    // create the index using packing algorithm
    auto index = std::make_shared<cityscape::spatial::SpatialIndex>(leaves);
    REQUIRE(index->size() == n);

    // find nearest values to a point
    auto result_n = index->knn(query_p, 1);
    auto closet_p = result_n.at(0).first;

    // Test query result id
    REQUIRE(closet_p.id() == 0);
    // Check query result name
    REQUIRE(closet_p.name() == "spatial0");
  }
}
