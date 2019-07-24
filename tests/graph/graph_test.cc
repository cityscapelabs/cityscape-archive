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

    // Add node
    SECTION("Add node") {
      cityscape::id_t nid = 1;
      // Name
      std::string name = "osm123";
      // Create a node with an id of 1
      auto node = std::make_shared<cityscape::graph::Node>(nid, name);
      // Test node id
      REQUIRE(node->id() == 1);
      // Check name
      REQUIRE(node->name() == name);

      // Check number of nodes
      REQUIRE(graph->nnodes() == 0);

      // Add node to graph
      REQUIRE(graph->add_node(node) == true);
      // Adding a duplicate node should fail
      REQUIRE(graph->add_node(node) == false);

      // Check number of nodes
      REQUIRE(graph->nnodes() == 1);
    }

    // Create an edge
    SECTION("Create an edge") {
      // Create a graph with an id of 0
      auto graph = std::make_shared<cityscape::graph::Graph>(0);

      // Create a node with an id of 0
      auto node0 = std::make_shared<cityscape::graph::Node>(0, "osm0");
      // Add node to graph
      REQUIRE(graph->add_node(node0) == true);
      REQUIRE(graph->nnodes() == 1);

      // Create a node with an id of 1
      auto node1 = std::make_shared<cityscape::graph::Node>(1, "osm1");
      // Add node to graph
      REQUIRE(graph->add_node(node1) == true);
      REQUIRE(graph->nnodes() == 2);

      // Directed edges
      SECTION("Create directed edges") {
        // Number of edges
        REQUIRE(graph->nedges() == 0);

        // Create edge 0 -> 1
        REQUIRE(graph->create_edge("osm0", "osm1", true) == true);
        REQUIRE(graph->nedges() == 1);

        // Create edge 1 -> 0
        REQUIRE(graph->create_edge("osm1", "osm0", true) == true);
        REQUIRE(graph->nedges() == 2);

        // Non-existant edge
        REQUIRE(graph->create_edge("osm0", "osm2", true) == false);

        // Duplicate nodes
        REQUIRE(graph->create_edge("osm0", "osm0", true) == false);
        REQUIRE(graph->nedges() == 2);
      }

      // Undirected edges
      SECTION("Create undirected edges") {
        // Number of edges
        REQUIRE(graph->nedges() == 0);

        // Create edge
        REQUIRE(graph->create_edge("osm0", "osm1", false) == true);
        REQUIRE(graph->nedges() == 2);

        // Non-existant edge
        REQUIRE(graph->create_edge("osm2", "osm1", false) == false);
        REQUIRE(graph->nedges() == 2);
      }
    }
  }
}
