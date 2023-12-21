#include <catch2/catch_test_macros.hpp>

#include "ProgressBar.h"

TEST_CASE("constructing, setting, and getting") {
    ProgressBar pb;
    REQUIRE(pb.getLength() == 70);
    REQUIRE(pb.getProgress() == 0);
    pb.setLength(30);
    pb.setProgress(0.5);
    REQUIRE(pb.getLength() == 30);
    REQUIRE(pb.getProgress() == 0.5);
}

TEST_CASE("toString method") {
    ProgressBar pb(5);
    REQUIRE(pb.toString() == "[     ] 0.00%");
    pb.setProgress(0.35);
    REQUIRE(pb.toString() == "[==   ] 35.00%");
    pb.setProgress(1);
    REQUIRE(pb.toString() == "[=====] 100.00%");
}
