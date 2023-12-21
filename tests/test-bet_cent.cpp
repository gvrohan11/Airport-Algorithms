#include <catch2/catch_test_macros.hpp>

#include "readdat.h"

#include <iostream>

#include "Algorithms/bet_cent.h"

using namespace std;

// IF THERE ARE NO ARROW SIGNS (-> or <-) ASSUME NODES ARE CONNECTED IN BOTH DIRECTIONS

TEST_CASE("Betweenness Centrality Dijkstra Simple") {

    /*
    
    |1| <--> |3| <--> |2| --> |4|
    
    */

    Graph g;

    g.addNode(1, "air1", 0, 1);
    g.addNode(2, "air2", 0, 2);
    g.addNode(3, "air3", 0, 3);
    g.addNode(4, "air4", 0, 4);

    g.connect(1, 3);
    g.connect(3, 2);
    g.connect(2, 3);
    g.connect(3, 1);
    g.connect(2, 4);

    BetweenessCentrality betcent;

    map<int, int> test = betcent.getAllScores(g, false, false);

    REQUIRE(test[1] == 0);
    REQUIRE(test[2] == 2);
    REQUIRE(test[3] == 3);
    REQUIRE(test[4] == 0);

}

TEST_CASE("Min Frequency Simple") {

    Graph g;

    g.addNode(1, "air1", 0, 1);
    g.addNode(2, "air2", 0, 2);
    g.addNode(3, "air3", 0, 3);
    g.addNode(4, "air4", 0, 4);

    g.connect(1, 3);
    g.connect(3, 2);
    g.connect(2, 3);
    g.connect(3, 1);
    g.connect(2, 4);

    BetweenessCentrality betcent;

    map<int, int> test = betcent.getAllScores(g, false, false);

    // Min Frequency = 2
    set<int> airport_freq_test1 = betcent.getAirportsWithMinFrequency(2);

    REQUIRE((int) airport_freq_test1.size() == 2);
    REQUIRE(airport_freq_test1.find(2) != airport_freq_test1.end());
    REQUIRE(airport_freq_test1.find(3) != airport_freq_test1.end());
    REQUIRE(airport_freq_test1.find(1) == airport_freq_test1.end());
    REQUIRE(airport_freq_test1.find(4) == airport_freq_test1.end());

    // Min Frequency = 3
    set<int> airport_freq_test2 = betcent.getAirportsWithMinFrequency(3);

    REQUIRE((int) airport_freq_test2.size() == 1);
    REQUIRE(airport_freq_test2.find(2) == airport_freq_test2.end());
    REQUIRE(airport_freq_test2.find(3) != airport_freq_test2.end());
    REQUIRE(airport_freq_test2.find(1) == airport_freq_test2.end());
    REQUIRE(airport_freq_test2.find(4) == airport_freq_test2.end());


}

TEST_CASE("Betweeness Centrality Dijkstra Complex") {

    /*
    

                     |4|
                    /  \
            |1|    /    \
             |   |3|----|5|----|6|
             |  /       /        \
             | /       /          \
            |2|      |8|          |7|
    
    
    */

    Graph g;

    g.addNode(1, "air1", 0, 1);
    g.addNode(2, "air2", 0, 2);
    g.addNode(3, "air3", 0, 3);
    g.addNode(4, "air4", 0, 4);
    g.addNode(5, "air5", 0, 5);
    g.addNode(6, "air6", 0, 6);
    g.addNode(7, "air7", 0, 7);
    g.addNode(8, "air8", 0, 8);

    g.connect(1, 2);
    g.connect(2, 1);
    g.connect(2, 3);
    g.connect(3, 2);
    g.connect(3, 4);
    g.connect(4, 3);
    g.connect(3, 5);
    g.connect(5, 3);
    g.connect(4, 5);
    g.connect(5, 4);
    g.connect(5, 6);
    g.connect(6, 5);
    g.connect(6, 7);
    g.connect(7, 6);
    g.connect(5, 8);
    g.connect(8, 5);

    BetweenessCentrality betcent;

    map<int, int> test = betcent.getAllScores(g, false, false);

    REQUIRE(test[1] == 0);
    REQUIRE(test[2] == 12);
    REQUIRE(test[3] == 20);
    REQUIRE(test[4] == 0);
    REQUIRE(test[5] == 28);
    REQUIRE(test[6] == 12);
    REQUIRE(test[7] == 0);
    REQUIRE(test[8] == 0);

}

TEST_CASE("Min Frequency Complex") {
    Graph g;

    g.addNode(1, "air1", 0, 1);
    g.addNode(2, "air2", 0, 2);
    g.addNode(3, "air3", 0, 3);
    g.addNode(4, "air4", 0, 4);
    g.addNode(5, "air5", 0, 5);
    g.addNode(6, "air6", 0, 6);
    g.addNode(7, "air7", 0, 7);
    g.addNode(8, "air8", 0, 8);

    g.connect(1, 2);
    g.connect(2, 1);
    g.connect(2, 3);
    g.connect(3, 2);
    g.connect(3, 4);
    g.connect(4, 3);
    g.connect(3, 5);
    g.connect(5, 3);
    g.connect(4, 5);
    g.connect(5, 4);
    g.connect(5, 6);
    g.connect(6, 5);
    g.connect(6, 7);
    g.connect(7, 6);
    g.connect(5, 8);
    g.connect(8, 5);

    BetweenessCentrality betcent;

    map<int, int> test = betcent.getAllScores(g, false, false);

    set<int> hubs = betcent.getAirportsWithMinFrequency(12);

    REQUIRE(hubs.find(1) == hubs.end());
    REQUIRE(hubs.find(2) != hubs.end());
    REQUIRE(hubs.find(3) != hubs.end());
    REQUIRE(hubs.find(4) == hubs.end());
    REQUIRE(hubs.find(5) != hubs.end());
    REQUIRE(hubs.find(6) != hubs.end());
    REQUIRE(hubs.find(7) == hubs.end());
    REQUIRE(hubs.find(8) == hubs.end());
}

TEST_CASE("Betweeness Centrality Dijkstra Unconnected") {

    /*
    
        |1|-------|2|          |6|----->|5|-------|7|
                  /                      |
                 /                       |
                /                       |4|
              |3|
    
    */

    Graph g;

    g.addNode(1, "air1", 0, 1);
    g.addNode(2, "air2", 0, 2);
    g.addNode(3, "air3", 0, 3);
    g.addNode(4, "air4", 0, 4);
    g.addNode(5, "air5", 0, 5);
    g.addNode(6, "air6", 0, 6);
    g.addNode(7, "air7", 0, 7);

    g.connect(1,2);
    g.connect(2,1);
    g.connect(2,3);
    g.connect(3,2);

    g.connect(6,5);
    g.connect(5,7);
    g.connect(7,5);
    g.connect(5,4);
    g.connect(4,5);


    BetweenessCentrality betcent;

    map<int, int> test = betcent.getAllScores(g, false, false);

    REQUIRE(test[1] == 0);
    REQUIRE(test[2] == 2);
    REQUIRE(test[3] == 0);
    REQUIRE(test[4] == 0);
    REQUIRE(test[5] == 4);
    REQUIRE(test[6] == 0);
    REQUIRE(test[7] == 0);

}

TEST_CASE("Min Frequency Unconnected") {
    Graph g;

    g.addNode(1, "air1", 0, 1);
    g.addNode(2, "air2", 0, 2);
    g.addNode(3, "air3", 0, 3);
    g.addNode(4, "air4", 0, 4);
    g.addNode(5, "air5", 0, 5);
    g.addNode(6, "air6", 0, 6);
    g.addNode(7, "air7", 0, 7);

    g.connect(1,2);
    g.connect(2,1);
    g.connect(2,3);
    g.connect(3,2);

    g.connect(6,5);
    g.connect(5,7);
    g.connect(7,5);
    g.connect(5,4);
    g.connect(4,5);

    BetweenessCentrality betcent;

    map<int, int> test = betcent.getAllScores(g, false, false);

    set<int> hubs = betcent.getAirportsWithMinFrequency(2);

    REQUIRE(hubs.find(1) == hubs.end());
    REQUIRE(hubs.find(2) != hubs.end());
    REQUIRE(hubs.find(3) == hubs.end());
    REQUIRE(hubs.find(4) == hubs.end());
    REQUIRE(hubs.find(5) != hubs.end());
    REQUIRE(hubs.find(6) == hubs.end());
    REQUIRE(hubs.find(7) == hubs.end());
}

TEST_CASE("Betweeness Centrality Probabilistic") {

    cout << "Starting Probabilistic Test Case..." << endl;

    vector<int> ids;

    for (int i = 0; i <= 1000; i += 1) {
        ids.push_back(i);
    }

    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", ids);

    cout << g.size() << " airports added" << endl;

    BetweenessCentrality betcent;

    map<int, int> probabilistic_map = betcent.getProbabilisticScores(g, 35, true, true, false);

    REQUIRE((int)probabilistic_map.size() <= g.size());

    set<int> probabilistic_set = betcent.getAirportsWithMinFrequency(2);
}

TEST_CASE ("Betweeness Centrality Probabilistic (Skip non-Paths False) ") {

    cout << "Starting Probabilistic Test Case (Skip non-Paths False)..." << endl;

    vector<int> ids;

    for (int i = 0; i <= 1000; i += 1) {
        ids.push_back(i);
    }

    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat", ids);

    cout << g.size() << " airports added" << endl;

    BetweenessCentrality betcent;

    map<int, int> probabilistic_map = betcent.getProbabilisticScores(g, 35, false, true, false);

    REQUIRE((int)probabilistic_map.size() <= g.size());

    set<int> probabilistic_set = betcent.getAirportsWithMinFrequency(2);
}
