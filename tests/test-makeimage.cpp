#include <catch2/catch_test_macros.hpp>

#include "Algorithms/makeimage.h"
#include "readdat.h"

using namespace std;
using cs225::PNG;
using cs225::HSLAPixel;

TEST_CASE("point creation") {
    PNG test;
    test.readFromFile("../Data/map.png");
    HSLAPixel p1 = HSLAPixel(100, 0.5, 0.5);
    HSLAPixel p2 = HSLAPixel(270, 1, 0.5);
    plotPoint(test, 20, -30, 10.5, p1);
    plotPoint(test, -80, 100, 45, p2); // this point goes out of bounds
    test.writeToFile("test-point.png");
    PNG expected;
    expected.readFromFile("../tests/test_images/expected-point.png");
    REQUIRE(test == expected);
}

TEST_CASE("line creation") {
    PNG test;
    test.readFromFile("../Data/map.png");
    HSLAPixel p1 = HSLAPixel(100, 0.2, 0.5);
    HSLAPixel p2 = HSLAPixel(0, 1, 0.8);
    plotLine(test, -30.5, -30.2, 20.666, 50.1, 17, p1); // flat; positive
    plotLine(test, -80, 100, 70, 0, 6, p2); // steep; negative; overlaps
    plotLine(test, -70, 125, 100, 300, 64, p1); // out of bounds; really thick
    test.writeToFile("test-line.png");
    PNG expected;
    expected.readFromFile("../tests/test_images/expected-line.png");
    REQUIRE(test == expected);
}

TEST_CASE("path creation") {
    PNG test;
    test.readFromFile("../Data/map.png");
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    HSLAPixel p1 = HSLAPixel(150, 0.7, 0.2);
    HSLAPixel p2 = HSLAPixel(210.5, 0.5, 0.5, 0.5);
    vector<int> path = {1, 1000, 2000, 3000, 4000, 6000};
    plotPath(test, g, path, 5, 4, p1, p2);
    test.writeToFile("test-path.png");
    PNG expected;
    expected.readFromFile("../tests/test_images/expected-path.png");
    REQUIRE(test == expected);
}

TEST_CASE("graph plotting") {
    PNG test;
    test.readFromFile("../Data/map.png");
    vector<int> ids;
    for (int i = 1; i <= 1000; i++) {
        ids.push_back(i);
    }
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", ids);
    PNG test_graph_no_edges = plotGraph(test, g, false, false);
    PNG test_graph_edges = plotGraph(test, g, true, false);
    test_graph_no_edges.writeToFile("test_graph_no_edges.png");
    test_graph_edges.writeToFile("test_graph_edges.png");
    PNG expected_graph_no_edges;
    PNG expected_graph_edges;
    expected_graph_no_edges.readFromFile("../tests/test_images/expected_graph_no_edges.png");
    expected_graph_edges.readFromFile("../tests/test_images/expected_graph_edges.png");
    REQUIRE(test_graph_no_edges == expected_graph_no_edges);
    REQUIRE(test_graph_edges == expected_graph_edges);
}

TEST_CASE("dijkstra plotting") {
    PNG test;
    test.readFromFile("../Data/map.png");
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");
    PNG test_dijkstra = plotDijkstra(test, g, 3319, 5554);
    test_dijkstra.writeToFile("test_dijkstra.png");
    PNG expected_dijkstra;
    expected_dijkstra.readFromFile("../tests/test_images/expected_dijkstra.png");
    REQUIRE(test_dijkstra == expected_dijkstra);
}

TEST_CASE("bfs plotting") {
    PNG test;
    test.readFromFile("../Data/map.png");
    vector<int> ids;
    for (int i = 0; i <= 5000; i += 5) {
        ids.push_back(i);
    }
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", ids);
    PNG test_bfs = plotBFS(test, g, 2990);
    test_bfs.writeToFile("test_bfs.png");
    PNG expected_bfs;
    expected_bfs.readFromFile("../tests/test_images/expected_bfs.png");
    REQUIRE(test_bfs == expected_bfs);
}

TEST_CASE("betweeness centrality plotting") {
    PNG test;
    test.readFromFile("../Data/map.png");
    vector<int> ids;
    for (int i = 0; i <= 500; i += 5) {
        ids.push_back(i);
    }
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", ids);
    cout << "Calculating betweenness centrality ... " << endl;
    PNG test_bc = plotBetweenness(test, g, true);
    test_bc.writeToFile("test_bc.png");
    PNG expected_bc;
    expected_bc.readFromFile("../tests/test_images/expected_bc.png");
    REQUIRE(test_bc == expected_bc);
}
