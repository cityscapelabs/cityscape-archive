#include "catch.hpp"

#include "line.h"
#include "spatial_index.h"
#include <boost/geometry.hpp>
#include <iostream>

// Check Spatial point class
TEST_CASE("Spatial line", "[spatial][line]") {
  const double Tolerance = 1.E-7;
  // Test point
  SECTION("Test point") {
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

    // Line Name
    std::string name = "line0";
    // Create a line with an id of 0
    auto line = std::make_shared<cityscape::spatial::Line>(src, dest, eid);
    line->weight(13.756);

    // check properties
    REQUIRE(line->src()->id() == src->id());
    REQUIRE(line->dest()->get_y() == dest->get_y());
    REQUIRE(line->weight() == Approx(13.756).epsilon(Tolerance));
    // check boost feature
//    std::cout << "line: " << line->points()[0]->id() << ";"
//              << line->points()[1]->id() << std::endl;
    std::cout << bg::wkt<cityscape::spatial::Line>(*line) << std::endl;
    REQUIRE(boost::geometry::length(*line) == Approx(10).epsilon(Tolerance));



    //    auto index = std::make_shared<cityscape::spatial::SpatialIndex<
    //        std::shared_ptr<cityscape::spatial::Line>>>();
    //    index->insert(line);
      }
  }