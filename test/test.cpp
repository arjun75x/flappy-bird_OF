//
//  test.cpp
//  test
//
//  Created by Arjun Arun on 4/2/18.
//

#include <stdio.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "util.hpp"

TEST_CASE("Speed Calculator Test") {
    SECTION("Base Speed Test") {
        REQUIRE(SpeedCalculator(1) == 1.5);
    }
    SECTION("Max Speed Test") {
        REQUIRE(SpeedCalculator(100) == Approx(6.500064));
    }
}
