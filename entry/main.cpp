#include "readdat.h"
#include "Algorithms/dijkstra.h"
#include "Algorithms/bfs.h"
#include "Algorithms/bet_cent.h"
#include "Algorithms/makeimage.h"

using namespace std;
using cs225::PNG;
using cs225::HSLAPixel;

int main() {
    // example usage
    Graph g = readData("../Data/airports.dat",  "../Data/routes.dat");

    cout << g.size() << " airports and " << g.connections() << " connections" << endl;

    int source = 3319;
    int target = 5554;
    PNG worldMap;
    worldMap.readFromFile("../Data/map.png");

    cs225::PNG output = plotDijkstra(worldMap, g, source, target, 8.5, 6, HSLAPixel(100, 0.5, 0.5), HSLAPixel(300, 0.7, 0.3));
    output.writeToFile("../entry/dij_example.png");

    cs225::PNG bfs = plotBFS(worldMap, g, source);
    bfs.writeToFile("../entry/bfs_example.png");

}
