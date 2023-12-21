#include "bfs.h"

using namespace std;

vector<int> BFS::traversalOfBFS(const Graph& g, int startID) {
	pathOfBFS_.clear();
	setAllFalse(g);
	queued_.push(startID);
	visited_[startID] = true;
	while(!queued_.empty()) {
		int present = queued_.front();
		queued_.pop();
		pathOfBFS_.push_back(present);
		for (int id : g.getConnections(present)) {
			if (!visited_[id]) {
				visited_[id] = true;
				queued_.push(id);
			}
		}
	}
	return pathOfBFS_;
}

void BFS::setAllFalse(const Graph& g) {
	for (int i : g.getIDs()) {
		visited_[i] = false;
	} 
}

vector<int> BFS::getPath() {
	return pathOfBFS_;
}
