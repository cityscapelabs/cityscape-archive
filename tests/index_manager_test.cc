#include "catch.hpp"

#include "index_manager.h"

// Check index manager class
TEST_CASE("Check IndexManager class", "[index]") {
  // Test node
  SECTION("Test index creation") {

    // Create a new index
    auto idx = std::make_shared<cityscape::IndexManager>();
    // Check current index
    REQUIRE(idx->current_index() == 0);

    // Check max index value
    REQUIRE(idx->max() == std::numeric_limits<cityscape::id_t>::max());

    // Create new indexs
    REQUIRE(idx->create_index() == 1);
    REQUIRE(idx->create_index() == 2);
  }
}
