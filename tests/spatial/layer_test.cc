#include "catch.hpp"
#include "layer.h"

// Check Spatial point class
TEST_CASE("Spatial layer check", "[spatial][layer]") {

  using namespace cityscape;
  using Point = spatial::Point2d;
  const double Tolerance = 1.E-7;

  // Test layer
  SECTION("Test layer creating") {
    // id
    cityscape::id_t lid = 1;
    // Tag
    std::string tag = "pipeline";
    // Create a graph with an id of 1
    auto layer = std::make_shared<spatial::Layer<Point>>(lid, tag);

    // Test graph id
    REQUIRE(layer->id() == lid);
    REQUIRE(layer->check_tag(tag) == true);

    // Add node
    SECTION("Add node") {
      cityscape::id_t nid = 1;
      // Name
      std::string name = "osm123";
      // Coordinates
      const std::array<double, 2> coordinates = {1.5, 2.4};
      // Create a node with an id of 1
      auto point = std::make_shared<Point>(nid, name, coordinates);
      // Test node id
      REQUIRE(point->id() == 1);
      // Check name
      REQUIRE(point->name() == name);

      // Check number of nodes
      REQUIRE(layer->nnodes() == 0);

      // Add node to graph
      REQUIRE(layer->add_node(point) == true);
      // Adding a duplicate node should fail
      REQUIRE(layer->add_node(point) == false);

      // Check number of nodes
      REQUIRE(layer->nnodes() == 1);
    }
  }
  // Create an edge
  SECTION("Create an segment") {
    // Create a graph with an id of 0
    auto layer = std::make_shared<spatial::Layer<Point>>(0);

    // Create a point with an id of 0
    std::array<double, 2> coords0 = {0., 1.};
    auto point0 = std::make_shared<Point>(0, "osm0", coords0);
    // Add node to graph
    REQUIRE(layer->add_node(point0) == true);
    REQUIRE(layer->nnodes() == 1);

    // Create a node with an id of 1
    std::array<double, 2> coords1 = {0., 2.};
    auto point1 = std::make_shared<Point>(1, "osm1", coords1);
    // Add node to graph
    REQUIRE(layer->add_node(point1) == true);
    REQUIRE(layer->nnodes() == 2);

    // Directed edges
    SECTION("Create directed edges") {
      // Number of edges
      REQUIRE(layer->nedges() == 0);

      // Create edge 0 -> 1
      REQUIRE(layer->create_edge("osm0", "osm1", true) == true);
      auto seg0 = layer->segment(0, 1);
      REQUIRE(layer->nedges() == 1);
      REQUIRE(seg0->src()->connect_degree() == 1);
      REQUIRE(seg0->dest()->connect_degree() == 1);
      REQUIRE(boost::geometry::length(*seg0) == Approx(1).epsilon(Tolerance));

      // Create edge 1 -> 0
      REQUIRE(layer->create_edge("osm1", "osm0", true) == true);
      REQUIRE(layer->nedges() == 2);
      REQUIRE(layer->segment(1, 0)->src()->connect_degree() == 2);
      REQUIRE(layer->segment(1, 0)->dest()->connect_degree() == 2);

      // Non-existant edge
      REQUIRE(layer->create_edge("osm0", "osm2", true) == false);

      // Duplicate nodes
      REQUIRE(layer->create_edge("osm0", "osm0", true) == false);
      REQUIRE(layer->nedges() == 2);
      REQUIRE(layer->segment(0, 1)->src()->connect_degree() == 2);
      REQUIRE(layer->segment(0, 1)->dest()->connect_degree() == 2);
    }

    // Undirected edges
    SECTION("Create undirected edges") {
      // Number of edges
      REQUIRE(layer->nedges() == 0);

      // Create edge
      REQUIRE(layer->create_edge("osm0", "osm1", false) == true);
      auto seg0 = layer->segment(0, 1);
      REQUIRE(layer->nedges() == 2);

      // Non-existant edge
      REQUIRE(layer->create_edge("osm2", "osm1", false) == false);
      REQUIRE(layer->nedges() == 2);
    }
  }
  SECTION("Spatial Indexing test") {
    auto layer = std::make_shared<spatial::Layer<Point>>(0);
    // create some points for storing
    // Coordinates
    const std::array<double, 2> coordinates0 = {1.5, 2.4};
    const std::array<double, 2> coordinates1 = {1.8, 2.4};
    const std::array<double, 2> coordinates2 = {3, 4};

    auto p0 = std::make_shared<Point>(0, "spatial0", coordinates0);
    auto p1 = std::make_shared<Point>(1, "spatial1", coordinates1);
    auto p2 = std::make_shared<Point>(2, "spatial2", coordinates2);

    // add points
    REQUIRE(layer->add_node(p0) == true);
    REQUIRE(layer->add_node(p1) == true);
    REQUIRE(layer->add_node(p2) == true);
    // add some segments (edges)
    layer->create_edge("spatial0", "spatial1", true);
    layer->create_edge("spatial0", "spatial2", true);
    layer->create_edge("spatial1", "spatial2", true);

    auto point_index = layer->point_index();
    auto segment_index = layer->segment_index();

    REQUIRE(point_index->size() == 3);
    REQUIRE(segment_index->size() == 3);

    SECTION("Layer Indexing features test") {
      // create a query point
      Point query_p(3, "query point", {1.3, 2.2});
      // find nearest values to a point
      auto result_n0 = point_index->knn(query_p, 1);
      auto closet_p = result_n0.at(0);

      // Test query result id
      REQUIRE(closet_p->id() == 0);
      // Check query result name
      REQUIRE(closet_p->name() == "spatial0");

      // find nearest segment to a point
      auto result_n1 = segment_index->knn(query_p, 1);
      auto closet_seg = result_n1.at(0);

      // Test query result id
      REQUIRE(closet_seg->id() == 0);
    }
  }
}