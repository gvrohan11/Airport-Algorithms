#pragma once

#include "Graph.h"

#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>

#include "readdat.h"

using namespace std;

/**
 * Class for Dijktra Algorithm
 * Generates an instance of shortest traversal between two points
 */
class Dijkstras {
    public:
        /**
        * @brief Generates a the shortest path of airports from source to target
        * @param g network of all airports
        * @param source the source airport ID
        * @param b the target airport ID
        * @return chronological vector of airport IDs from source to target
        */
        vector<int> getPath(const Graph& g, int source, int target);

        /**
        * @brief shortest distance of the particular instance
        * @return The distance between the airports, accounting for the Earth's curvature
        */
        double shortestDistance() {
            return shortestDistance_;
        }

    private:

        /**
        * @brief list of all airports
        */
        vector<int> airports_; 
        /**
        * @brief maps source airport connections to its distance
        */
        unordered_map<int, double> ports_;
        /**
        * @brief maps airport's previous airport
        */
        map<int, int> prev_; // maps airport's previous immediate source
        /**
        * @brief shorteset distance for intended algorithm
        */
        double shortestDistance_;
      
};
