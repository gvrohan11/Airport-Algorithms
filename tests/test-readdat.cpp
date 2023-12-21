#include <catch2/catch_test_macros.hpp>

#include "readdat.h"
#include "Graph.h"
#include <algorithm>

using namespace std;

TEST_CASE("basic readline test") {
    string numbers = "1-2-3-4-5-6-7-8-9-10";
    stringstream ss(numbers);
    vector<string> actual = readline(ss, '-');
    vector<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    REQUIRE(actual == expected);

    string words = "I like to code in C++";
    stringstream ss2(words);
    vector<string> actual2 = readline(ss2, ' ');
    vector<string> expected2 = {"I", "like", "to", "code", "in", "C++"};
    REQUIRE(actual2 == expected2);
}

TEST_CASE("readline with quotes") {
    string recipe =  "eggs butter \"soy milk\" flour";
    stringstream ss(recipe);
    vector<string> actual = readline(ss, ' ');
    vector<string> expected = {"eggs", "butter", "soy milk", "flour"};
    REQUIRE(actual == expected);
}

TEST_CASE("delim at ends") {
    string cities = ",chicago,boston,atlanta,";
    stringstream ss(cities);
    vector<string> actual = readline(ss, ',');
    vector<string> expected = {"", "chicago", "boston", "atlanta", ""};
    REQUIRE(actual == expected);
}

TEST_CASE("valid id") {
    int id1 = 31415;
    int id2 = -20;
    int id3 = 0;
    int id4 = 1;

    REQUIRE(validID(id1) == true);
    REQUIRE(validID(id2) == false);
    REQUIRE(validID(id3) == false);
    REQUIRE(validID(id4) == true);
}

TEST_CASE("valid iata") {
    string iata1 = "ABC";
    string iata2 = "B14";
    string iata3 = "YEET";
    string iata4 = "ABC!";
    string iata5 = "abc";

    REQUIRE(validIATA(iata1) == true);
    REQUIRE(validIATA(iata2) == false);
    REQUIRE(validIATA(iata3) == false);
    REQUIRE(validIATA(iata4) == false);
    REQUIRE(validIATA(iata5) == false);
}

TEST_CASE("valid longitude and latitude") {
    double val1 = 0;
    double val2 = -45.1;
    double val3 = 90;
    double val4 = 130.75;
    double val5 = -180;
    double val6 = 200.6;

    REQUIRE(validLatitude(val1) == true);
    REQUIRE(validLatitude(val2) == true);
    REQUIRE(validLatitude(val3) == true);
    REQUIRE(validLatitude(val4) == false);
    REQUIRE(validLatitude(val5) == false);
    REQUIRE(validLatitude(val6) == false);

    REQUIRE(validLongitude(val1) == true);
    REQUIRE(validLongitude(val2) == true);
    REQUIRE(validLongitude(val3) == true);
    REQUIRE(validLongitude(val4) == true);
    REQUIRE(validLongitude(val5) == true);
    REQUIRE(validLongitude(val6) == false);
}

TEST_CASE("readData without ids") {
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    REQUIRE(g.size() == 7698);
    REQUIRE(g.connections() == 67074);
}

TEST_CASE("readData with ids") {
    vector<int> ids = {1, 2, 3, 4};
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", ids);
    REQUIRE(g.size() == 4);
    REQUIRE(g.connections() == 12); // All these airports are connected to each other, so 3 * 4 = 12
    vector<int> actual = g.getIDs();
    sort(actual.begin(), actual.end());
    REQUIRE(actual == ids);
}

TEST_CASE("sampleData") {
    Graph g = sampleData("../Data/airports.dat",  "../Data/routes.dat", 1000);
    REQUIRE(g.size() == 1000);
    REQUIRE(g.connections() < 67074);
    // this is more than the number of IDs in the data
    g = sampleData("../Data/airports.dat",  "../Data/routes.dat", 10000);
    REQUIRE(g.size() == 7698);
    REQUIRE(g.connections() == 67074);
}
