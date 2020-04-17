#include "catch.hpp"

#include "segment.h"
#include "spatial_index.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <iostream>

// Check Spatial point class
TEST_CASE("Spatial line", "[spatial][line]") {
  typedef bg::model::box<cityscape::spatial::Point> box;
  const double Tolerance = 1.E-7;
  cityscape::id_t nid0 = 0;
  cityscape::id_t nid1 = 1;
  cityscape::id_t eid = 0;
  // Name
  const std::string name0 = "spatial0";
  const std::string name1 = "spatial1";
  // Coordinates
  const std::array<double, 2> coordinates0 = {0, 0};
  const std::array<double, 2> coordinates1 = {0, 10};
  // Create two points
  auto src =
      std::make_shared<cityscape::spatial::Point>(nid0, name0, coordinates0);
  auto dest =
      std::make_shared<cityscape::spatial::Point>(nid1, name1, coordinates1);
  // A test point
  const std::array<double, 2> coordinate = {1, 0};
  auto test_p = std::make_shared<cityscape::spatial::Point>(111, "test_point",
                                                            coordinate);

  // Seg Name
  std::string tag = "seg0";
  // Create a line with an id of 0
  auto seg = std::make_shared<cityscape::spatial::Segment>(src, dest, eid, tag);
  seg->weight(13.756);

  // Test segment
  SECTION("Test seg basic properties") {
    // check basic properties
    REQUIRE(seg->src()->id() == src->id());
    REQUIRE(seg->dest()->get_y() == dest->get_y());
    REQUIRE(seg->weight() == Approx(13.756).epsilon(Tolerance));
    // Test seg id
    REQUIRE(seg->id() == eid);
    // Check tag
    REQUIRE(seg->check_tag(tag) == true);
  }
  SECTION("Test seg boost properties") {
    // check boost feature
    //    std::cout << bg::wkt<cityscape::spatial::Segment>(*seg) << std::endl;
    REQUIRE(boost::geometry::length(*seg) == Approx(10).epsilon(Tolerance));

    REQUIRE(boost::geometry::distance(*seg, *seg) ==
            Approx(0).epsilon(Tolerance));
    REQUIRE(boost::geometry::distance(*test_p, *seg) ==
            Approx(1).epsilon(Tolerance));
    // test on using with boost point
    bg::model::point<double, 2, bg::cs::cartesian> point2(1.0, 2.0);
    REQUIRE(boost::geometry::distance(point2, *seg) ==
            Approx(1).epsilon(Tolerance));
  }
}