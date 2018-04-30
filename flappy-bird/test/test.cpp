//
//  test.cpp
//  test
//
//  Created by Arjun Arun on 4/2/18.
//

#include <stdio.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ofApp.h"

TEST_CASE("Speed Calculator Tests") {
    ofApp *test = new ofApp();
    SECTION("Base Speed Test") {
        REQUIRE(test->SpeedCalculator(1) == 1.5);
    }
    SECTION("Max Speed Test") {
        REQUIRE(test->SpeedCalculator(10) == test->SpeedCalculator(7));
    }
}
