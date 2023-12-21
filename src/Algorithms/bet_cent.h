#pragma once

#include "Graph.h"
#include "readdat.h"
#include "dijkstra.h"
#include "../ProgressBar.h"

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <set>

using namespace std;

class BetweenessCentrality {
    public:

        /**
        * @brief Applies Betweeness Centrality, incorporated with Dijkstras Algorithm
        * to calculate scores (frquencies) for each airport
        * Airport scores are determined by the number of appearences on the shortest paths
        * between all airports
        *
        * @param graph The graph on which to apply betweenness centrality
        * @param showProgress Whether to show a progress bar
        * @param displayResults Whether to print number of airports added and betweeness scores 
        * @return map<int, int> A map of Airport IDs to betweenness scores
        */
        map<int, int> getAllScores(const Graph& graph, bool showProgress = true, bool displayResults = false);

        /**
        * @brief Finds the airports with a min betweeness centrality score
        * The higher the score, the more established an airport is as a "hub"
        *
        * @param frequency minimum frequency requirement for airport Ids to be added to the set
        * @return set<int> a set of airport IDs with a minimum betweeness score
        */
        set<int> getAirportsWithMinFrequency(int frequency);

        /**
        * @brief Applies the betweenness centrality algorithm with a probabilistic approach
        * Instead of considering all pairs of distinct points, uniformly samples a given
        * amount of pairs of distinct points
        *
        * @param graph The graph on which to apply betweenness centrality
        * @param sampleSize How many paths to sample from the graph
        * @param skipNonPaths Whether to skip pairs of points with no path
        * @param showProgress Whether to show a progress bar
        * @param displayResults Whether to print number of airports added and betweeness scores 
        * @return map<int, int> A map of Airport IDs to betweenness scores
        */
        map<int, int> getProbabilisticScores(const Graph& graph, int sampleSize, bool skipNonPaths = true, bool showProgress = true, bool displayResults = false);

    private:
        vector<int> airport_ids_; // vector of all airport ids

        map<int, int> airport_scores_; // maps airport to Betweenness Centrality Score

};

