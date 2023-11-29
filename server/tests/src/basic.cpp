#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "Server.hpp"

TEST_CASE("Basic test", "[basic]")
{
    REQUIRE(basic_test());
}
