#include <limits>

#include "catch.hpp"

#include "edge.h"

// Check Graph edge class
TEST_CASE("Graph edge", "[graph][edge]") {
  // Test edge
  SECTION("Test edge creating") {
    // Create source and destination node
    cityscape::id_t snid = 0;
    cityscape::id_t dnid = 1;

    auto src = std::make_shared<cityscape::graph::Node>(snid);
    auto dest = std::make_shared<cityscape::graph::Node>(dnid);

    cityscape::id_t eid = 1;
    // Create a edge with an id of max
    auto edge = std::make_shared<cityscape::graph::Edge>(src, dest, eid);
    // Test edge id
    REQUIRE(edge->id() == 1);
  }
}
