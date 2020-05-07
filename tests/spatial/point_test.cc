#include "catch.hpp"

#include "point.h"
#include "point_2d.h"
#include "point_3d.h"

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
        std::make_shared<cityscape::spatial::Point<2>>(nid, name, coordinates);
    // Test point id
    REQUIRE(point->id() == 1);
    // Check name
    REQUIRE(point->name() == name);

    // Check coordinates
    auto x = point->get<0>();
    auto y = point->get<1>();

    REQUIRE(x == Approx(coordinates.at(0)).epsilon(Tolerance));
    REQUIRE(y == Approx(coordinates.at(1)).epsilon(Tolerance));
  }

  // Check nodal ids
  SECTION("Point id max") {
    cityscape::id_t nid = std::numeric_limits<cityscape::id_t>::max();
    // Name
    const std::string name = "spatial123";
    // Coordinates
    const std::array<double, 2> coordinates = {1.5, 2.4};

    // Create a point with an id of max
    auto point =
        std::make_shared<cityscape::spatial::Point<2>>(nid, name, coordinates);
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
    // Coordinates
    const std::array<double, 2> coordinates = {1.5, 2.4};
    // Create a point with an id of 0 and a house tag
    auto point = std::make_shared<cityscape::spatial::Point<2>>(
        nid, name, coordinates, tag);

    // Test point id
    REQUIRE(point->id() == 0);

    // Check if tag is present
    REQUIRE(point->check_tag(tag) == true);
    REQUIRE(point->check_tag("") == false);
    REQUIRE(point->check_tag("roud") == false);
  }
  //
  SECTION("Test Boost Geometry distances") {
    // Coordinates for 2d
    std::array<double, 2> coords1 = {1., 1.};
    cityscape::spatial::Point<2> p1{1, "s1", coords1};

    std::array<double, 2> coords2 = {2., 2.};
    cityscape::spatial::Point<2> p2{2, "s2", coords2};

    REQUIRE(boost::geometry::distance(p1, p2) ==
            Approx(1.414213562).epsilon(Tolerance));

    // Coordinates for 3d
    std::array<double, 3> coords3 = {0, 0, 0};
    cityscape::spatial::Point<3> p3{1, "s1", coords3};

    std::array<double, 3> coords4 = {1, 1, 1};
    cityscape::spatial::Point<3> p4{2, "s2", coords4};

    REQUIRE(boost::geometry::distance(p3, p4) ==
            Approx(1.7320508076).epsilon(Tolerance));
  }

  SECTION("Test Point 2d") {
    // Coordinates for 2d
    std::array<double, 2> coords1 = {1., 1.};
    cityscape::spatial::Point2d p1{1, "s1", coords1};

    std::array<double, 2> coords2 = {2., 2.};
    cityscape::spatial::Point2d p2{2, "s2", coords2};

    std::vector<std::shared_ptr<cityscape::graph::Node>> test;
    test.emplace_back(std::make_shared<cityscape::spatial::Point2d>(p1));

    REQUIRE(boost::geometry::distance(p1, p2) ==
            Approx(1.414213562).epsilon(Tolerance));
  }
  SECTION("Test Point 3d") {
    // Coordinates for 2d
    std::array<double, 3> coords3 = {0, 0, 0};
    cityscape::spatial::Point3d p3{1, "s1", coords3};

    std::array<double, 3> coords4 = {1, 1, 1};
    cityscape::spatial::Point3d p4{2, "s2", coords4};

    REQUIRE(boost::geometry::distance(p3, p4) ==
            Approx(1.7320508076).epsilon(Tolerance));
  }
  SECTION("Test Point with radians coordinate") {
    namespace bg = boost ::geometry;
    // Coordinates for 2d
    std::array<double, 2> coords1 = {23.725750, 37.971536};
    cityscape::spatial::Point<2, bg::cs::geographic<bg ::degree>> p1{1, "s1",
                                                                     coords1};

    std::array<double, 2> coords2 = {4.3826169, 50.8119483};
    cityscape::spatial::Point<2, bg::cs::geographic<bg ::degree>> p2{2, "s2",
                                                                     coords2};

    REQUIRE(boost::geometry::distance(p1, p2) ==
            Approx(2088389.0786590837).epsilon(Tolerance));
  }
}
