#include "catch.hpp"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <chrono>

// to store queries results
#include <vector>

#include "point.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

// Check Spatial point class
TEST_CASE("Spatial point index", "[spatial][point]") {
  typedef cityscape::spatial::Point Point;
  typedef std::pair<Point, unsigned> value;
  const double Tolerance = 1.E-7;
  // create some points for storing
  const std::vector<Point> points{Point(0, "spatial0", {1.5, 2.4}),
                                  Point(1, "spatial1", {1.8, 2.4}),
                                  Point(2, "spatial2", {3, 4})};
  const unsigned n = 3;
  // create a query point
  Point query_p(3, "query point", {1.3, 2.2});

  SECTION("Boost r tree no packing") {
    // create the rtree using default constructor
    bgi::rtree<value, bgi::rstar<4, 2> > rtree;

    for (unsigned i = 0; i < n; ++i) {
      auto p = points.at(i);
      // insert new value
      rtree.insert(std::make_pair(p, i));
    }

    // find nearest values to a point
    std::vector<value> result_n;
    rtree.query(bgi::nearest(query_p, 1), std::back_inserter(result_n));
    auto found_p = result_n.at(0).first;

    // Test query result id
    REQUIRE(found_p.id() == 0);
    // Check query result name
    REQUIRE(found_p.name() == "spatial0");
  }

  SECTION("Boost r tree with packing") {
    std::vector<value> values;
    // create some values
    for (unsigned i = 0; i < n; ++i) {
      auto p = points.at(i);
      // insert new value
      values.emplace_back(std::make_pair(p, i));
    }
    // create the rtree using packing algorithm
    bgi::rtree<value, bgi::rstar<4, 2> > rtree(values);

    // find nearest values to a point
    std::vector<value> result_n;
    rtree.query(bgi::nearest(query_p, 1), std::back_inserter(result_n));
    auto found_p = result_n.at(0).first;

    // Test query result id
    REQUIRE(found_p.id() == 0);
    // Check query result name
    REQUIRE(found_p.name() == "spatial0");
  }
}
