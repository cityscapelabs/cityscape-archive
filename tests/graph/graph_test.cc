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
  SECTION("Create test graph") {
    // Create a graph with an id of 0
    auto graph = std::make_shared<cityscape::graph::Graph>(0);

    // Create nodes
    auto node0 = std::make_shared<cityscape::graph::Node>(0, "osm0");
    auto node1 = std::make_shared<cityscape::graph::Node>(1, "osm1");
    auto node2 = std::make_shared<cityscape::graph::Node>(2, "osm2");
    auto node3 = std::make_shared<cityscape::graph::Node>(3, "osm3");
    auto node4 = std::make_shared<cityscape::graph::Node>(4, "osm4");
    auto node5 = std::make_shared<cityscape::graph::Node>(5, "osm5");
    REQUIRE(graph->add_node(node0) == true);
    std::cout << "Nodal id: " << node0->id() << std::endl;
    REQUIRE(graph->add_node(node1) == true);
    REQUIRE(graph->add_node(node2) == true);
    REQUIRE(graph->add_node(node3) == true);
    REQUIRE(graph->add_node(node4) == true);
    REQUIRE(graph->add_node(node5) == true);

    // Create edges
    REQUIRE(graph->create_edge("osm0", "osm1", true) == true);
    REQUIRE(graph->create_edge("osm0", "osm2", true) == true);
    REQUIRE(graph->create_edge("osm0", "osm5", true) == true);
    REQUIRE(graph->create_edge("osm1", "osm2", true) == true);
    REQUIRE(graph->create_edge("osm1", "osm3", true) == true);
    REQUIRE(graph->create_edge("osm2", "osm0", true) == true);
    REQUIRE(graph->create_edge("osm2", "osm3", true) == true);
    REQUIRE(graph->create_edge("osm2", "osm5", true) == true);
    REQUIRE(graph->create_edge("osm3", "osm2", true) == true);
    REQUIRE(graph->create_edge("osm3", "osm4", true) == true);
    REQUIRE(graph->create_edge("osm4", "osm5", true) == true);

    // Add weights
    (graph->edge(0, 1))->weight(1.5);
    (graph->edge(0, 2))->weight(9.1);
    (graph->edge(0, 5))->weight(14.3);
    (graph->edge(1, 2))->weight(15.9);
    (graph->edge(1, 3))->weight(5.5);
    (graph->edge(2, 0))->weight(5.6);
    (graph->edge(2, 3))->weight(11.6);
    (graph->edge(2, 5))->weight(2.4);
    (graph->edge(3, 2))->weight(0.2);
    (graph->edge(3, 4))->weight(6.2);
    (graph->edge(4, 5))->weight(9.7);

    // Check weights
    REQUIRE((graph->edge(0, 1))->weight() == Approx(1.5).epsilon(Tolerance));
    REQUIRE((graph->edge(0, 2))->weight() == Approx(9.1).epsilon(Tolerance));
    REQUIRE((graph->edge(0, 5))->weight() == Approx(14.3).epsilon(Tolerance));
    REQUIRE((graph->edge(1, 2))->weight() == Approx(15.9).epsilon(Tolerance));
    REQUIRE((graph->edge(1, 3))->weight() == Approx(5.5).epsilon(Tolerance));
    REQUIRE((graph->edge(2, 0))->weight() == Approx(5.6).epsilon(Tolerance));
    REQUIRE((graph->edge(2, 3))->weight() == Approx(11.6).epsilon(Tolerance));
    REQUIRE((graph->edge(2, 5))->weight() == Approx(2.4).epsilon(Tolerance));
    REQUIRE((graph->edge(3, 2))->weight() == Approx(0.2).epsilon(Tolerance));
    REQUIRE((graph->edge(3, 4))->weight() == Approx(6.2).epsilon(Tolerance));
    REQUIRE((graph->edge(4, 5))->weight() == Approx(9.7).epsilon(Tolerance));

    // Run Dijkstra Priority Queue
    const auto source = "osm0";
    const auto destination = "osm5";
    const auto path = graph->dijkstra(source, destination);
    // Check distances
    REQUIRE(path.size() == 5);
  }
}
