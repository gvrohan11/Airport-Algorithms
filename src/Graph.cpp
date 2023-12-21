#include "Graph.h"
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

double Graph::GraphNode::_connectionDistance(int id) const {
    return _connectedTo(id) ? connections_.at(id) : numeric_limits<double>::infinity();
}

void Graph::addNode(int id, string name, double latitude, double longitude) {
    GraphNode node = GraphNode(name, latitude, longitude);
    nodes_[id] = node;
}

void Graph::removeNode(int id) {
    GraphNode toRemove = nodes_.at(id);
    numConnections_ -= toRemove.connections_.size();
    nodes_.erase(id);
    for (auto it = nodes_.begin(); it != nodes_.end(); it++) {
        GraphNode node = it->second;
        if (node.connections_.find(id) != node.connections_.end()) {
            node.connections_.erase(id);
            numConnections_--;
        }
    }
}

void Graph::connect(int id1, int id2) {
    nodes_[id1].connections_[id2] = _distance(id1, id2);
    numConnections_++;
}

void Graph::disconnect(int id1, int id2) {
    nodes_[id1].connections_.erase(id2);
    numConnections_--;
}

vector<int> Graph::getIDs(bool sorted) const {
    vector<int> ids;
    for (auto it = nodes_.begin(); it != nodes_.end(); it++) {
        ids.push_back(it->first);
    }
    if (sorted) { sort(ids.begin(), ids.end()); }
    return ids;
}

vector<int> Graph::getConnections(int id, bool sorted) const {
    vector<int> ids;
    GraphNode gn = nodes_.at(id);
    for (auto it = gn.connections_.begin(); it != gn.connections_.end(); it++) {
        ids.push_back(it->first);
    }
    if (sorted) { sort(ids.begin(), ids.end()); }
    return ids;
}

bool Graph::connectedTo(int id1, int id2) const {
    return nodes_.at(id1)._connectedTo(id2);
}

double Graph::_distance(int id1, int id2) const {
    GraphNode a = nodes_.at(id1);
    GraphNode b = nodes_.at(id2);
    if (spherical_) {
        double PI = 4*atan(1);
        //haversine formula
        double EARTH_RADIUS = 6378.1;
        double lat1 = a.latitude_ * PI/180;
        double lat2 = b.latitude_ * PI/180;
        double deltalat = lat1 - lat2;
        double deltalong = (b.longitude_ - a.longitude_) * PI/180;
        double haversine1 = pow(sin(deltalat/2),2)+cos(lat1)*cos(lat2)*pow(sin(deltalong/2),2);
        double haversine2 = 2*atan2(sqrt(haversine1), sqrt(1-haversine1));
        return haversine2 * EARTH_RADIUS;
    } else {
        double deltalat = a.latitude_ - b.latitude_;
        double deltalong = a.longitude_ - b.longitude_;
        return sqrt(pow(deltalat, 2) + pow(deltalong, 2));
    }
}
