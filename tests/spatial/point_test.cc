#include "catch.hpp"

#include "point.h"

// Check Spatial point class
TEST_CASE("Spatial point", "[spatial][point]") {
  const double Tolerance = 1.E-7;
  // Test point
  SECTION("Test point") {
    cityscape::id_t nid = 1;
    // Name
    const std::string name = "spatial0";
    // Coordinates
    const std::array<double, 2> coordinates = {1.5, 2.4};
    // Create a point with an id of 1
    auto point =
        std::make_shared<cityscape::spatial::Point>(nid, name, coordinates);
    // Test point id
    REQUIRE(point->id() == 1);
    // Check name
    REQUIRE(point->name() == name);

    // Check coordinates
    auto coords = point->coordinates();
    REQUIRE(coords.size() == 2);
    REQUIRE(coords.at(0) == Approx(coordinates.at(0)).epsilon(Tolerance));
    REQUIRE(coords.at(1) == Approx(coordinates.at(1)).epsilon(Tolerance));

    // Check nodal ids
    SECTION("Point id max") {
      cityscape::id_t nid = std::numeric_limits<cityscape::id_t>::max();
      // Name
      const std::string name = "spatial123";

      // Create a point with an id of max
      auto point =
          std::make_shared<cityscape::spatial::Point>(nid, name, coordinates);
      // Test point id
      REQUIRE(point->id() == std::numeric_limits<cityscape::id_t>::max());
    }

    // Test point tags
    SECTION("Test point tags") {
      cityscape::id_t nid = 0;
      // Name
      const std::string name = "spatial123";
      // Tag
      const std::string tag = "house";
      // Create a point with an id of 0 and a house tag
      auto point = std::make_shared<cityscape::spatial::Point>(
          nid, name, coordinates, tag);

      // Test point id
      REQUIRE(point->id() == 0);

      // Check if tag is present
      REQUIRE(point->check_tag(tag) == true);
      REQUIRE(point->check_tag("") == false);
      REQUIRE(point->check_tag("roud") == false);
    }

    SECTION("Test Boost Geometry distances") {
      // Coordinates
      std::array<double, 2> coords1 = {1., 1.};
      cityscape::spatial::Point p1{1, "s1", coords1};

      std::array<double, 2> coords2 = {2., 2.};
      cityscape::spatial::Point p2{2, "s2", coords2};

      REQUIRE(boost::geometry::distance(p1, p2) ==
              Approx(1.414213562).epsilon(Tolerance));
    }
  }
}
