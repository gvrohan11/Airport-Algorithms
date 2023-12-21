#pragma once
#include "../Graph.h"
#include <vector>
#include <map>
#include <queue>


using namespace std;
class BFS {
    public:
    /**
    * @brief Traversies through the graph
    *
    * @param g the given graph to traverse through
    * @param startID the starting point of traversal
    * @return a vector of all ids in order of when they were visited
    */
    vector<int> traversalOfBFS(const Graph& g, int startID);

    /**
    * @brief gets the path of the traversal
    *
    * @return a vector of all ids in order of when they were visited
    */
    vector<int> getPath();


    private:

    /**
    * @brief stores the queued ids for traversal
    */
    queue<int> queued_;

    /**
    * @brief stores data of weather or not the id's were visited
    */
    map<int, bool> visited_;

    /**
    * @brief stores the list of ids visited through BFS
    */
    vector<int> pathOfBFS_;

    /**
    * @brief a helper function to set all nodes as n ot visited
    *
    * @param g the given graph to set nodes for
    */
    void setAllFalse(const Graph& g);
};
