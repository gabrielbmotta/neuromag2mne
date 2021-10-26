#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int test(){return 1;};

TEST_CASE("Dummy Test" , "[text]"){
  REQUIRE(test() == 1);
  REQUIRE(test() == 2);
}