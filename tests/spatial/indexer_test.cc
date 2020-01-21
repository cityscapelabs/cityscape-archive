#include "catch.hpp"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <chrono>

#include "s2/base/commandlineflags.h"
#include "s2/s1chord_angle.h"
#include "s2/s2closest_point_query.h"
#include "s2/s2earth.h"
#include "s2/s2point_index.h"

// to store queries results
#include <vector>

// just for output
#include <boost/foreach.hpp>
#include <iostream>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
using namespace std::chrono;

float randloat(float min, float max) {
  float r = (float)std::rand() / (float)RAND_MAX;
  return min + r * (max - min);
}

// Check Spatial point class
TEST_CASE("Performance test for spatial index ", "[spatial][index]") {
  typedef bg::model::point<float, 2, bg::cs::cartesian> point;
  typedef std::pair<point, unsigned> value;

  const double Tolerance = 1.E-7;
  unsigned n = 1000000;
  unsigned n_q = 100000;
  unsigned k = 10;

  std::vector<std::pair<double, double> > coordinates(n);
  std::vector<std::pair<double, double> > q_coordinates(n_q);
  // creates points for testing
  for (unsigned i = 0; i < n; ++i) {
    // create a point
    auto latitude = randloat(-90, 90);
    auto longitude = randloat(-180, 180);
    auto coord = std::make_pair(latitude, longitude);
    coordinates[i] = coord;
  }

  for (unsigned i = 0; i < n_q; ++i) {
    // create a point
    auto latitude = randloat(-90, 90);
    auto longitude = randloat(-180, 180);
    auto coord = std::make_pair(latitude, longitude);
    q_coordinates[i] = coord;
  }

  // Test point
  SECTION("Boost r tree no packing") {
    auto start = std::chrono::high_resolution_clock::now();
    // create the rtree using default constructor
    bgi::rtree<value, bgi::rstar<4, 2> > rtree;
    // create some values
    for (unsigned i = 0; i < n; ++i) {
      auto coord = coordinates[i];
      // create a box
      point p = point(coord.first, coord.second);
      // insert new value
      rtree.insert(std::make_pair(p, i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    std::cout << "Instertion time for rtree with rstar algorithm :"
              << duration.count() << std::endl;

    // find 10 nearest values to a point
    auto start_q = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < n_q; ++i) {
      std::vector<value> result_n;
      auto coord = q_coordinates[i];
      point p = point(coord.first, coord.second);
      rtree.query(bgi::nearest(p, k), std::back_inserter(result_n));
      // compute distance as well (like s2)
      for (unsigned i = 0; i < k; ++i) {
        point p2 = point(randloat(-90, 90), randloat(-180, 180));
        boost::geometry::distance(p, p2);
      }
    }
    auto end_q = std::chrono::high_resolution_clock::now();
    auto duration_q = duration_cast<milliseconds>(end_q - start_q);
    std::cout << "query time for rtree :" << duration_q.count() << std::endl;
  }
  SECTION("Boost r tree with packing") {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<value> points(n);
    // create some values
    for (unsigned i = 0; i < n; ++i) {
      auto coord = coordinates[i];
      // create a point
      point p = point(coord.first, coord.second);
      // insert new value
      points[i] = (std::make_pair(p, i));
    }
    // create the rtree using packing algorithm
    bgi::rtree<value, bgi::rstar<4, 2> > rtree(points);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    std::cout << "Instertion time for rtree with packing :" << duration.count()
              << std::endl;

    // find 10 nearest values to a point
    auto start_q = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < n_q; ++i) {
      std::vector<value> result_n;
      auto coord = q_coordinates[i];
      point p = point(coord.first, coord.second);
      rtree.query(bgi::nearest(p, k), std::back_inserter(result_n));
      for (unsigned i = 0; i < k; ++i) {
        point p2 = point(randloat(-90, 90), randloat(-180, 180));
        boost::geometry::distance(p, p2);
      }
    }

    auto end_q = std::chrono::high_resolution_clock::now();
    auto duration_q = duration_cast<milliseconds>(end_q - start_q);
    std::cout << "query time for rtree with packing:" << duration_q.count()
              << std::endl;
  }
  SECTION("Google S2 ") {
    S2PointIndex<unsigned> index;

    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < n; ++i) {
      auto coord = coordinates[i];
      S2Point point(S2LatLng::FromDegrees(coord.first, coord.second));
      index.Add(point, i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    std::cout << "Instertion time for s2point :" << duration.count()
              << std::endl;

    // k nearest neighbor
    S2ClosestPointQuery<unsigned> query(&index);
    query.mutable_options()->set_max_results(k);

    auto start_q = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < n_q; ++i) {
      auto coord = q_coordinates[i];
      S2Point point(S2LatLng::FromDegrees(coord.first, coord.second));
      S2ClosestPointQuery<int>::PointTarget target(point);
      query.FindClosestPoints(&target);
    }
    auto end_q = std::chrono::high_resolution_clock::now();
    auto duration_q = duration_cast<milliseconds>(end_q - start_q);

    std::cout << "query time for s2point :" << duration_q.count() << std::endl;
  }
}
