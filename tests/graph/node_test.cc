#include <limits>

#include "catch.hpp"

#include "node.h"

// Check Graph node class
TEST_CASE("Graph node", "[graph][node]") {
  // Test node
  SECTION("Test node") {
    cityscape::id_t nid = 1;
    // Create a node with an id of max
    auto node = std::make_shared<cityscape::graph::Node>(nid);
    // Test node id
    REQUIRE(node->id() == 1);

    // Check nodal ids
    SECTION("Node id max") {
      cityscape::id_t nid = std::numeric_limits<cityscape::id_t>::max();

      // Create a node with an id of max
      auto node = std::make_shared<cityscape::graph::Node>(nid);
      // Test node id
      REQUIRE(node->id() == std::numeric_limits<cityscape::id_t>::max());
    }
  }
}
