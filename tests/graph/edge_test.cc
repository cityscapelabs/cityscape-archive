#include "catch.hpp"

#include "edge.h"

// Check Graph edge class
TEST_CASE("Graph edge", "[graph][edge]") {
  const double Tolerance = 1.E-7;
  // Test edge
  SECTION("Test edge creating") {
    // Create source and destination node
    cityscape::id_t snid = 0;
    cityscape::id_t dnid = 1;
    // Name
    std::string name = "osm123";

    auto src = std::make_shared<cityscape::graph::Node>(snid, name);
    auto dest = std::make_shared<cityscape::graph::Node>(dnid, name);

    cityscape::id_t eid = 1;
    // Create a edge with an id of 1
    auto edge = std::make_shared<cityscape::graph::Edge>(src, dest, eid);
    // Test edge id
    REQUIRE(edge->id() == 1);

    // Test edge tags
    SECTION("Test edge tags") {
      cityscape::id_t eid = 0;
      // Tag
      std::string tag = "road";
      // Create a edge with an id of 0 and a road tag
      auto edge = std::make_shared<cityscape::graph::Edge>(src, dest, eid, tag);

      // Test edge id
      REQUIRE(edge->id() == 0);

      // Check if tag is present
      REQUIRE(edge->check_tag(tag) == true);
      REQUIRE(edge->check_tag("") == false);
      REQUIRE(edge->check_tag("pipe") == false);
    }

    // Test edge weights
    SECTION("Test edge weights") {
      cityscape::id_t eid = 0;
      // Tag
      std::string tag = "road";
      // Create a edge with an id of 0 and a road tag
      auto edge = std::make_shared<cityscape::graph::Edge>(src, dest, eid, tag);

      // Test edge weight
      REQUIRE(edge->weight() == Approx(0.).epsilon(Tolerance));

      // Update edge weight and test
      edge->weight(13.756);
      REQUIRE(edge->weight() == Approx(13.756).epsilon(Tolerance));

      // Check for max and min weights
      edge->weight(std::numeric_limits<double>::max());
      REQUIRE(edge->weight() ==
              Approx(std::numeric_limits<double>::max()).epsilon(Tolerance));

      edge->weight(std::numeric_limits<double>::min());
      REQUIRE(edge->weight() ==
              Approx(std::numeric_limits<double>::min()).epsilon(Tolerance));
    }
  }
}
