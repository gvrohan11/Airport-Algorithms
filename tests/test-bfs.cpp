#include <catch2/catch_test_macros.hpp>
 
#include "readdat.h"
 
#include <iostream>
#include <stdexcept>

#include "Algorithms/bfs.h"


TEST_CASE("Disconected Graph") {
 
   Graph g(false);
 
   g.addNode(1, "one", 0, 1);
   g.addNode(2, "two", 0, 2);
   g.addNode(3, "three", 0, 3);
   g.addNode(4, "four", 1, 3);
   g.addNode(5, "five", 1, 6);
   g.addNode(6, "six", 1, 7);

   g.connect(1, 2);
   g.connect(2, 1);
   g.connect(2, 3);
   g.connect(3, 2);

   g.connect(5, 6);
   g.connect(6, 5);

   BFS bfs;
   vector<int> actual = bfs.traversalOfBFS(g, 5);
   vector<int> expected = {5, 6};
 
   REQUIRE(actual == expected);

   actual = bfs.traversalOfBFS(g, 4);
   expected = {4};
   REQUIRE(actual == expected);

   actual = bfs.traversalOfBFS(g, 1);
   expected = {1, 2, 3};
   REQUIRE(actual == expected);
}

TEST_CASE("Simple traversal") {
 
   Graph g(false);
 
   g.addNode(1, "one", 0, 1);
   g.addNode(2, "two", 0, 2);
   g.addNode(3, "three", 0, 3);
   g.addNode(4, "four", 1, 3);
   g.addNode(5, "five", 1, 6);
   g.connect(1, 2);
   g.connect(2, 1);
   g.connect(2, 4);
   g.connect(4, 2);
   g.connect(1, 3);
   g.connect(3, 1);
   g.connect(1, 4);
   g.connect(4, 1);
   g.connect(3, 4);
   g.connect(4, 3);
   g.connect(3, 5);
   g.connect(5, 3);
 
   BFS bfs;
   vector<int> actual = bfs.traversalOfBFS(g, 1);
   vector<int> expected = {1, 2, 3, 4, 5};
 
   REQUIRE(actual == expected);

   actual = bfs.traversalOfBFS(g, 3);
   expected = {3, 1, 4, 5, 2};
   REQUIRE(actual == expected);

}

TEST_CASE("All set false") {
 
   Graph g(false);
 
   g.addNode(1, "one", 0, 1);
   g.addNode(2, "two", 0, 2);
   g.addNode(3, "three", 0, 3);
   g.addNode(4, "four", 1, 3);
   g.addNode(5, "five", 1, 6);
   g.addNode(6, "six", 1, 1);
   g.connect(1, 2);
   g.connect(2, 4);
   g.connect(1, 3);
   g.connect(1, 4);
   g.connect(3, 4);
   g.connect(3, 5);
 
   BFS bfs;
   vector<int> actual = bfs.traversalOfBFS(g, 1);

   vector<int> expected = {1, 2, 3, 4, 5};

   REQUIRE(actual == expected);

   g.connect(1, 6);

   actual = bfs.traversalOfBFS(g, 1);

   expected = {1, 2, 3, 4, 6, 5};
 
   REQUIRE(actual == expected);
}


TEST_CASE("Globe Data") {
   Graph g(true);
   BFS bfs;
   /*
   *  ID: Number
   *  SJC: 3748 (San Jose)
   *  SFO: 3469 (San Francisco)
   *  ORD: 3830 (Chicago)
   *  LAX: 3484 (Los Angeles)
   *  NRT: 2279 (Tokyo)
   *  CMI: 4049 (Champaign)
   *  FNJ: 3377 (Pyongyang)
   *  RGO: 8830 (Chongjin)
   *  JFK: 3797 (New York)
   *  
   */
   vector<int> ids = {2279, 3484, 3469, 3830, 3748, 4049};
   g = readData("../Data/airports.dat", "../Data/routes.dat", ids);

   vector<int> actual = bfs.traversalOfBFS(g, 4049);
   // CMI -> ORD -> NRT -> SFO -> LAX -> SJC
   vector<int> expected = {4049, 3830, 2279, 3469, 3484, 3748};
   REQUIRE(actual == expected);

   ids = {2279, 3484, 3469, 3748, 4049};
   g = readData("../Data/airports.dat", "../Data/routes.dat", ids);
   actual = bfs.traversalOfBFS(g, 4049);
   expected = {4049};
   REQUIRE(actual == expected);
}
