#include "catch.hpp"

#include "graph.h"

// Check Graph graph class
TEST_CASE("Graph graph", "[graph]") {
  const double Tolerance = 1.E-7;
  // Test graph
  SECTION("Test graph creating") {
    // graph id
    cityscape::id_t gid = 1;
    // Create a graph with an id of 1
    auto graph = std::make_shared<cityscape::graph::Graph>(gid);
    // Test graph id
    REQUIRE(graph->id() == 1);

    // Test graph tags
    SECTION("Test graph tags") {
      cityscape::id_t gid = 0;
      // Tag
      std::string tag = "road";
      // Create a graph with an id of 0 and a road tag
      auto graph = std::make_shared<cityscape::graph::Graph>(gid, tag);

      // Test graph id
      REQUIRE(graph->id() == 0);

      // Check if tag is present
      REQUIRE(graph->check_tag(tag) == true);
      REQUIRE(graph->check_tag("") == false);
      REQUIRE(graph->check_tag("pipe") == false);
    }
  }
}
