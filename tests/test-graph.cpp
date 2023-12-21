#include <catch2/catch_test_macros.hpp>

#include "Graph.h"
#include "readdat.h"
#include <cmath>
#include <algorithm>

using namespace std;

double inf = numeric_limits<double>::infinity();

/**
* @brief Determines if two distance are close enough to be considered equal (within 2%)
* This accounts for the ellipticity of the Earth 
*
* @param distance1 The first distance
* @param distance2 The second distance
* @return double Whether the distances are close enough
*/
bool closeEnough(double distance1, double distance2) {
    return max(distance1, distance2) / min(distance1, distance2) < 1.02;
}

TEST_CASE("graph constructor") {
    Graph g;
    REQUIRE(g.connections() == 0);
    REQUIRE(g.size() == 0);
    REQUIRE(g.getIDs() == vector<int>());

    Graph g2(false);
    REQUIRE(g2.getIDs() == vector<int>());

    REQUIRE(!g2.getSpherical());
    g2.setSpherical(true);
    REQUIRE(g2.getSpherical());
}

TEST_CASE("adding/removing/accessing nodes") {
    Graph g;
    REQUIRE(!g.inGraph(12));
    REQUIRE(!g.inGraph(24));

    // add 12
    g.addNode(12, "idk", 30, -30);

    REQUIRE(g.connections() == 0);
    REQUIRE(g.size() == 1);
    REQUIRE(g.getIDs() == vector<int>(1,12));
    REQUIRE(g.getName(12) == "idk");
    REQUIRE(g.getLatitude(12) == 30);
    REQUIRE(g.getLongitude(12) == -30);
    REQUIRE(g.inGraph(12));
    REQUIRE(!g.inGraph(24));

    // add 24
    g.addNode(24, "smth", 25, -35);
    
    REQUIRE(g.connections() == 0);
    REQUIRE(g.size() == 2);
    vector<int> expected = {12, 24};
    vector<int> actual = g.getIDs();
    sort(actual.begin(), actual.end());
    REQUIRE(actual == expected);
    REQUIRE(g.getName(24) == "smth");
    REQUIRE(g.getLatitude(24) == 25);
    REQUIRE(g.getLongitude(24) == -35);
    REQUIRE(g.inGraph(12));
    REQUIRE(g.inGraph(24));

    // remove 24
    g.removeNode(24);

    REQUIRE(g.connections() == 0);
    REQUIRE(g.size() == 1);
    REQUIRE(g.getIDs() == vector<int>(1,12));
    REQUIRE(g.getName(12) == "idk");
    REQUIRE(g.getLatitude(12) == 30);
    REQUIRE(g.getLongitude(12) == -30);
    REQUIRE(g.inGraph(12));
    REQUIRE(!g.inGraph(24));

    // remove 12
    g.removeNode(12);

    REQUIRE(!g.inGraph(12));
    REQUIRE(!g.inGraph(24));
    REQUIRE(g.connections() == 0);
    REQUIRE(g.size() == 0);
    REQUIRE(g.getIDs() == vector<int>());
}

TEST_CASE("connecting/disconnecting nodes") {
    Graph g(false);
    g.addNode(12, "idk", 30, -30);
    g.addNode(24, "smth", 25, -35);

    REQUIRE(g.connections() == 0);
    REQUIRE(g.getConnections(12).size() == 0);
    REQUIRE(g.getConnections(24).size() == 0);
    REQUIRE(g.getDistance(12, 24) == inf);
    REQUIRE(g.getDistance(24, 12) == inf);
    REQUIRE(!g.connectedTo(12, 24));
    REQUIRE(!g.connectedTo(24, 12));
    
    // connect 12 to 24
    g.connect(12, 24);

    REQUIRE(g.connections() == 1);
    REQUIRE(g.getConnections(12) == vector<int>(1,24));
    REQUIRE(g.getConnections(24).size() == 0);
    REQUIRE(abs(g.getDistance(12, 24) - 5*sqrt(2)) <= 0.0001);
    REQUIRE(g.getDistance(24, 12) == inf);
    REQUIRE(g.connectedTo(12, 24));
    REQUIRE(!g.connectedTo(24, 12));

    // connected 24 to 12
    g.connect(24, 12);

    REQUIRE(g.connections() == 2);
    REQUIRE(g.getConnections(12) == vector<int>(1,24));
    REQUIRE(g.getConnections(24) == vector<int>(1,12));
    REQUIRE(abs(g.getDistance(12, 24) - 5*sqrt(2)) <= 0.0001 );
    REQUIRE(abs(g.getDistance(24, 12) - 5*sqrt(2)) <= 0.0001 );
    REQUIRE(g.getDistance(24, 12) < inf);
    REQUIRE(g.connectedTo(12, 24));
    REQUIRE(g.connectedTo(24, 12));

    // disconnect 24 to 12
    g.disconnect(24, 12);

    REQUIRE(g.connections() == 1);
    REQUIRE(g.getConnections(12) == vector<int>(1,24));
    REQUIRE(g.getConnections(24).size() == 0);
    REQUIRE(abs(g.getDistance(12, 24) - 5*sqrt(2)) <= 0.0001);
    REQUIRE(g.getDistance(24, 12) == inf);
    REQUIRE(g.connectedTo(12, 24));
    REQUIRE(!g.connectedTo(24, 12));

    // disconnect 12 to 24
    g.disconnect(12, 24);

    REQUIRE(g.connections() == 0);
    REQUIRE(g.getConnections(12).size() == 0);
    REQUIRE(g.getConnections(24).size() == 0);
    REQUIRE(g.getDistance(12, 24) == inf);
    REQUIRE(g.getDistance(24, 12) == inf);
    REQUIRE(!g.connectedTo(12, 24));
    REQUIRE(!g.connectedTo(24, 12));

}

TEST_CASE("complex removing nodes") {
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    REQUIRE(g.connections() == 67074);
    REQUIRE(g.size() == 7698);
    // remove 2
    g.removeNode(2);
    REQUIRE(g.connections() == 67074 - 14); // 14 was determined from routes.data
    REQUIRE(g.size() == 7698 - 1);

    REQUIRE(g.connectedTo(1, 3));
    // disconnect 1 to 3
    g.disconnect(1, 3);
    REQUIRE(!g.connectedTo(1, 3));
    REQUIRE(g.connectedTo(3, 1));

    REQUIRE(g.connections() == 67074 - 15);
    REQUIRE(g.size() == 7698 - 1);
}

TEST_CASE("distance function") {
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    // real-life distances are looked up beforehand
    // some airports aren't automatically connected
    REQUIRE(closeEnough(g.getDistance(1, 2), 106.80));
    REQUIRE(g.getDistance(26, 41) == inf);
    g.connect(26, 41);
    REQUIRE(closeEnough(g.getDistance(26, 41), 560.91));
    REQUIRE(g.getDistance(6332, 9751) == inf);
    g.connect(6332, 9751);
    REQUIRE(closeEnough(g.getDistance(6332, 9751), 17742.30));
    g.connect(1, 1); // this is nonsensical but just used to test a distance of 0
    REQUIRE(g.getDistance(1, 1) == 0);
}
