#include "makeimage.h"
#include <cmath>

using namespace std;
using cs225::PNG;
using cs225::HSLAPixel;

PNG plotGraph(PNG worldMap, Graph g, bool edges, bool showProgress, double pointSize, int lineThickness, HSLAPixel pointPixel, HSLAPixel linePixel) {
    vector<int> ids = g.getIDs();
    // plot connections
    if (edges) {
        ProgressBar pb;
        if (showProgress) {
            cout << pb;
        }
        for (size_t i = 0; i < ids.size(); i++) {
            for (size_t j = i + 1; j < ids.size(); j++) {
                int id1 = ids[i];
                int id2 = ids[j];
                // plot if connected
                if (g.connectedTo(id1, id2) || g.connectedTo(id2, id1)) {
                    plotLine(worldMap, g.getLatitude(id1), g.getLongitude(id1), g.getLatitude(id2), g.getLongitude(id2), lineThickness, linePixel);
                }
            }
            if (showProgress) {
                pb.setProgress((double) i / ids.size());
                cout << pb;
            }
        }
        if (showProgress) {
            pb.setProgress(1);
            cout << pb << endl;
        }
    }
    // plot airports
    for (int id : ids) {
        plotPoint(worldMap, g.getLatitude(id), g.getLongitude(id), pointSize, pointPixel);
    }
    return worldMap;
}

PNG plotDijkstra(PNG worldMap, Graph g, int source, int target, double pointSize, int lineThickness, HSLAPixel pointPixel, HSLAPixel linePixel) {
    Dijkstras dij;
    vector<int> path = dij.getPath(g, source, target);
    plotPath(worldMap, g, path, pointSize, lineThickness, pointPixel, linePixel);
    return worldMap;
}

PNG plotBFS(PNG worldMap, Graph g, int start, double pointSize, int lineThickness, HSLAPixel pointPixel, HSLAPixel linePixel) {
    BFS bfs;
    vector<int> path = bfs.traversalOfBFS(g, start);
    plotPath(worldMap, g, path, pointSize, lineThickness, pointPixel, linePixel);
    return worldMap;
}

PNG plotBetweenness(PNG worldMap, Graph g, bool showProgress, int sampleSize, bool skipNonPaths, double maxRadius, HSLAPixel pointPixel) {
    BetweenessCentrality bc;
    map<int, int> scores;
    if (sampleSize != 0) {
        scores = bc.getProbabilisticScores(g, sampleSize, skipNonPaths, showProgress);
    } else {
        scores = bc.getAllScores(g, showProgress);
    }
    int max = 0;
    for (auto it = scores.begin(); it != scores.end(); it++) {
        if (it->second > max) {
            max = it->second;
        }
    }
    for (auto it = scores.begin(); it != scores.end(); it++) {
        double ratio = (double) it->second / max;
        plotPoint(worldMap, g.getLatitude(it->first), g.getLongitude(it->first), maxRadius * ratio, pointPixel);
    }
    return worldMap;
}

void plotPath(cs225::PNG & worldMap, Graph g, vector<int> path, double pointSize, int lineThickness, HSLAPixel pointPixel, HSLAPixel linePixel) {
    // iterates over every airport in the path
    for (size_t i = 1; i < path.size(); i++) {
        int id1 = path[i-1];
        // draw a line between the previous airport and this one (excludes the first iteration)
        // the routes dataset doesn't specify whether the flight is eastward or westward so
        // it is assumed that the line doesn't wrap around the map
        int id2 = path[i];
        plotLine(worldMap, g.getLatitude(id1), g.getLongitude(id1), g.getLatitude(id2), g.getLongitude(id2), lineThickness, linePixel);
    }
    for (int id : path) {
        plotPoint(worldMap, g.getLatitude(id), g.getLongitude(id), pointSize, pointPixel);
    }
}

void plotPoint(PNG & worldMap, double lat, double lon, double radius, HSLAPixel pixel) {
    int halfWidth = worldMap.width() / 2;
    int halfHeight = worldMap.height() / 2;
    int centerX = (halfWidth * lon / 180) + halfWidth;
    int centerY = (halfHeight * -lat / 90) + halfHeight;
    // considers the square that circumscribes the point's circle
    for (int x = centerX - radius; x <= centerX + radius; x++) {
        for (int y = centerY - radius; y <= centerY + radius; y++) {
            // out of bounds check
            if (x < 0 || y < 0 || x >= (int) worldMap.width() || y >= (int) worldMap.height()) {
                continue;
            }
            int r2 = pow(x - centerX, 2) + pow(y - centerY, 2);
            // draw if inside the radius
            if (r2 < pow(radius, 2)) {
                worldMap.getPixel(x, y) = pixel;
            }
        }
    }
}

void plotLine(PNG & worldMap, double lat1, double lon1, double lat2, double lon2, int thickness, HSLAPixel pixel) {
    int halfThickness = thickness / 2;
    // repeats to make the line thicker
    for (int adj = -halfThickness; adj < -halfThickness + thickness; adj++) {
        int halfWidth = worldMap.width() / 2;
        int halfHeight = worldMap.height() / 2;
        int x1 = (halfWidth * lon1 / 180) + halfWidth;
        int y1 = (halfHeight * -lat1 / 90) + halfHeight;
        int x2 = (halfWidth * lon2 / 180) + halfWidth;
        int y2 = (halfHeight * -lat2 / 90) + halfHeight;
        int dy = y2 - y1;
        int dx = x2 - x1;
        // if the line is more flat than steep
        if (abs(dy) < abs(dx)) {
            // adjust for thickness reasons
            y1 += adj;
            y2 += adj;
            // make sure the second point is further right than the first
            if (x1 > x2) {
                swap(x1, x2);
                swap(y1, y2);
                dy *= -1;
                dx *= -1;
            }
            int yi = 1;
            if (dy < 0) {
                yi = -1;
                dy *= -1;
            }
            int d = 2 * dy - dx;
            int y = y1;
            // iterate over every x between x1 and x2
            for (int x = x1; x != x2; x++) {
                if (!(x < 0 || y < 0 || x >= (int) worldMap.width() || y >= (int) worldMap.height())) {
                    worldMap.getPixel(x, y) = pixel;
                }
                if (d > 0) {
                    y += yi;
                    d += 2 * (dy - dx);
                } else {
                    d += 2 * dy;
                }
            }
        // if the line is more steep than flat
        // this is basically the same as above with x and y swapped in most places
        } else {
            x1 += adj;
            x2 += adj;
            if (y1 > y2) {
                swap(x1, x2);
                swap(y1, y2);
                dx *= -1;
                dy *= -1;
            }
            int xi = 1;
            if (dx < 0) {
                xi = -1;
                dx *= -1;
            }
            int d = 2 * dx - dy;
            int x = x1;
            for (int y = y1; y != y2; y++) {
                if (!(x < 0 || y < 0 || x >= (int) worldMap.width() || y >= (int) worldMap.height())) {
                    worldMap.getPixel(x, y) = pixel;
                }
                if (d > 0) {
                    x += xi;
                    d += 2 * (dx - dy);
                } else {
                    d += 2 * dx;
                }
            }
        }
    }
}
