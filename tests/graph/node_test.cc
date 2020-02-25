#include "catch.hpp"

#include "node.h"

// Check Graph node class
TEST_CASE("Graph node", "[graph][node]") {
  // Test node
  SECTION("Test node") {
    cityscape::id_t nid = 1;
    // Name
    std::string name = "osm123";
    // Create a node with an id of 1
    auto node = std::make_shared<cityscape::graph::Node>(nid, name);
    // Test node id
    REQUIRE(node->id() == 1);
    // Check name
    REQUIRE(node->name() == name);

    // Check nodal ids
    SECTION("Node id max") {
      cityscape::id_t nid = std::numeric_limits<cityscape::id_t>::max();
      // Name
      std::string name = "osm123";

      // Create a node with an id of max
      auto node = std::make_shared<cityscape::graph::Node>(nid, name);
      // Test node id
      REQUIRE(node->id() == std::numeric_limits<cityscape::id_t>::max());
    }

    // Test node tags
    SECTION("Test node tags") {
      cityscape::id_t nid = 0;
      // Name
      std::string name = "osm123";
      // Tag
      std::string tag = "road";
      // Create a node with an id of 0 and a road tag
      auto node = std::make_shared<cityscape::graph::Node>(nid, name, tag);

      // Test node id
      REQUIRE(node->id() == 0);

      // Check if tag is present
      REQUIRE(node->check_tag(tag) == true);
      REQUIRE(node->check_tag("") == false);
      REQUIRE(node->check_tag("pipe") == false);

      // Add new Tag
      std::string new_tag = "pipe";
      node->add_tag(new_tag);
      REQUIRE(node->check_tag("pipe") == true);
    }
  }
}
