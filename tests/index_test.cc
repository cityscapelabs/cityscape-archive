#include "catch.hpp"

#include "index.h"

// Check index class
TEST_CASE("Check Index class", "[index]") {
  // Test node
  SECTION("Test index creation") {
    
    // Create a new index
    auto idx = std::make_shared<cityscape::Index>();
    // Check current id
    REQUIRE(idx->current_id() == 0);

    // Check max id value
    REQUIRE(idx->max() == std::numeric_limits<cityscape::id_t>::max());

    // Create new ids
    REQUIRE(idx->create_id() == 1);
    REQUIRE(idx->create_id() == 2);
  }
}
