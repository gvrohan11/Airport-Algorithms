#include "dijkstra.h"
#include <queue>
#include <iostream>
#include <set>
#include <limits>
#include <utility>

using namespace std;

typedef pair<int, double> DijNode;

vector<int> Dijkstras::getPath(const Graph& g, int source, int target) {
    airports_ = g.getIDs();
    // checks if source and targets are valid
    if (!g.inGraph(source) || !g.inGraph(target)) {
        return vector<int>();
    }
    auto comp = [](DijNode a, DijNode b) {
        return a.second > b.second;
    };
    priority_queue<DijNode, vector<DijNode>, decltype(comp)> qu(comp);
    map<int, double> ports_;
    map<int, int> prev_;

    // source to connection distance initialization
    for (int id : airports_) {
        if (source == id) {
            DijNode node(id, 0);
            qu.push(node);
            ports_[id] = 0;
        } else {
            DijNode node(id, numeric_limits<double>::infinity());
            qu.push(node);
            ports_[id] = numeric_limits<double>::infinity();
        }
        prev_[id] = -1;
    }

    set<int> seen; // checks if airport has been visited

    while (!qu.empty()) {
        auto node = qu.top();
        qu.pop();
        while (seen.find(node.first) != seen.end() && !qu.empty()) {
            node = qu.top();
            qu.pop();
        }
        seen.insert(node.first);
        vector<int> neighbors = g.getConnections(node.first);
        for (int adj : neighbors) {
            double alt = node.second + g.getDistance(node.first, adj);
            if (alt < ports_.at(adj)) {
                ports_[adj] = alt;
                prev_[adj] = node.first;
                qu.push(DijNode(adj, alt)); // removed a bunch of adj.first->id
            }
        }
    }
    // adds previous paths to vector
    int temp = target;
    vector<int> paths;
    while (temp != -1) {
        paths.push_back(prev_[temp]);
        temp = prev_.at(temp);
    }

    // reverses path to        
    reverse(paths.begin(), paths.end());
    paths.push_back(target);

    shortestDistance_ = ports_[target];

    // checks if no path exists
    if (paths.at(1) != source) {
        return vector<int>();
    }
    paths.erase(paths.begin());
    return paths;
}

