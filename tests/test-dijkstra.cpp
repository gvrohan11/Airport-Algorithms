#include <catch2/catch_test_macros.hpp>

#include "readdat.h"

#include <iostream>

#include "Algorithms/dijkstra.h"

using namespace std;


TEST_CASE("Simple Dijkstra") {

    cout << "------------------------------------------------" << endl;

    cout << "starting [Simple Dijkstra]" << endl;

    Graph g(false);

    /*
                |4|

    |1| ------- |2| ------- |3|


    */

    g.addNode(1, "one", 0, 1);
    g.addNode(2, "two", 0, 2);
    g.addNode(3, "three", 0, 3);
    g.addNode(4, "four", 1, 2);


    g.connect(1, 2);
    g.connect(2, 3);

    Dijkstras dij;
    vector<int> actual = dij.getPath(g, 1, 3);
    vector<int> expected = {1, 2, 3};

    cout << "Distance: " << dij.shortestDistance() << endl;

    REQUIRE(actual == expected);
}

TEST_CASE("Complex Dijkstra") {

    cout << "------------------------------------------------" << endl;

    /*
            |2| ----- |3|
          /            |
        /              |
    |1|                | 
        \              | 
         \             |
          |4| ------- |5|
                       |
                       |
                       |
                      |6|  
    */

    cout << "starting [Complex Dijkstra]" << endl;
    Graph g;

    g.addNode(1, "one", 0, 0);
    g.addNode(2, "two", 1, 1);
    g.addNode(3, "three", 2, 1);
    g.addNode(4, "four", 1, -1);
    g.addNode(5, "five", 2, -1);
    g.addNode(6, "six", 2, -2);

    g.connect(1, 2);
    g.connect(1, 4);
    g.connect(2, 4);
    g.connect(2, 3);
    g.connect(4, 5);
    g.connect(3, 5);
    g.connect(5, 6);

    Dijkstras dij;
    vector<int> actual = dij.getPath(g, 1, 6);
    vector<int> expected = {1, 4, 5, 6};

    REQUIRE(actual == expected);
}

TEST_CASE("No Path") {
    cout << "------------------------------------------------" << endl;

    /*
                      |5|  
                     /                   
                    /
                   / 
                  /  
                |4|


    |1| ------- |2| ------- |3|
    */

    cout << "starting [No Path]" << endl;
    Graph g;

    g.addNode(1, "one", 0, 1);
    g.addNode(2, "two", 0, 2);
    g.addNode(3, "three", 0, 3);
    g.addNode(4, "four", 1, 2);
    g.addNode(5, "five", 4, 4);

    g.connect(1, 2);
    g.connect(2, 3);
    g.connect(4, 5);

    Dijkstras dij;
    vector<int> actual = dij.getPath(g, 1, 5);
    // vector<int> expected = {1, 2, 3};

    REQUIRE(actual == vector<int>());
    REQUIRE(dij.shortestDistance() == numeric_limits<double>::infinity());
}

TEST_CASE("Dijkstra Airport Nearby") {

    Dijkstras canvas;

    cout << "------------------------------------------------" << endl;
    cout << "starting [Dijkstra Airport Nearby]" << endl;

    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    cout << g.size() << " airports added" << endl;

    Dijkstras dij;

    cout << "starting journey from Champaign to O'Hare: " << endl;

    int champ = 4049;
    int ohare = 3830;

    vector<int> vec1 = dij.getPath(g, champ, ohare);
    double minDist = dij.shortestDistance();
    double expec1 = g.getDistance(4049, 3830);

    for (auto i : vec1) {
        if (i == -1) continue;
        cout << g.getName(i) << " ---> ";
    }
    cout << "arrived to " << g.getName(ohare) << endl;

    vector<int> expected = {4049, 3830};

    cout << "Distance: " << dij.shortestDistance() << endl;

    REQUIRE(vec1 == expected);

    REQUIRE(minDist == expec1);

}


TEST_CASE("Dijkstra Airport Complex") {

    cout << "------------------------------------------------" << endl;

    cout << "starting [Dijkstra Airport Complex]" << endl;


    Dijkstras canvas;
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    Dijkstras dij;
    cout << "starting journey from Champaign to Hong Kong: " << endl;

    int champ = 4049;
    int hgk = 3077;

    vector<int> journey = dij.getPath(g, champ, hgk);

    double shortest = g.getDistance(4049, 3830);
    shortest += g.getDistance(3830, 3077);


    double alt_path = g.getDistance(4049, 3670); // Champaign to Dallas
    alt_path += g.getDistance(3670, 3690);  // Dallas to Nashville
    alt_path += g.getDistance(3690, 193);  // Nashville to Toronto
    alt_path += g.getDistance(193, 1382);   // Toronto to Paris
    alt_path += g.getDistance(1382, 3077);  // Paris to Hongkong

    for (auto i : journey) {
        if (i == -1) continue;
        cout << g.getName(i) << " ---> ";
    }
    cout << "arrived to " << g.getName(hgk) << endl;

    REQUIRE(alt_path > shortest);

    vector<int> expected = {4049, 3830, 3077};

    cout << "Distance: " << dij.shortestDistance() << endl;

    REQUIRE(dij.shortestDistance() == shortest);

    REQUIRE(journey == expected);
}


TEST_CASE("Alluitsup Paa, Greenland to Nanyuki, Kenya") {

    cout << "------------------------------------------------" << endl;

    cout << "starting [LLU to NYK]" << endl;


    int source = 5438;
    int target = 5695;
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    Dijkstras dij;
    auto path = dij.getPath(g, source, target);
    auto distance = dij.shortestDistance();

    for (auto i : path) {
        if (i == -1) continue;
        cout << g.getName(i) << " ---> ";
    }

    cout << "arrived to " << g.getName(target) << endl;

    cout << "Distance: " << distance << endl;


    REQUIRE(distance < 13000);
}


TEST_CASE("Chicago,Illinois to Windohek,Namibia") {
    cout << "------------------------------------------------" << endl;
    cout << "starting [ORD to WDH]" << endl;


    int target = 4105; // namibia
    int source = 3830; // IL, USA

    // subset of possible airport connections
    vector<int> sub = {3830, 1382, 4049, 1002, 8336, 
                            1003, 4105, 1004, 1059, 5662, 5663, 
                            5664, 13762, 963, 966, 1013, 5613, 
                            799, 1074, 248, 3797, 3576}; // Set Airports

    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", sub);
    Dijkstras dij;
    auto path = dij.getPath(g, source, target);
    auto distance = dij.shortestDistance();

    for (auto i : path) {
        if (i == -1) continue;
        cout << g.getName(i) << " ---> ";
    }
    cout << "arrived to " << g.getName(target) << endl;

    vector<int> expected = {3830, 3797, 248, 4105};
    cout << "Distance: " << distance << endl;

    REQUIRE(path == expected);
    cout << "------------------------------------------------" << endl;
    cout << "End of Dijkstra Test Cases" << endl;

}
