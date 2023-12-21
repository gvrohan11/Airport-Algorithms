#pragma once
#include "Algorithms/dijkstra.h"
#include "Algorithms/bet_cent.h"
#include "Algorithms/bfs.h"
#include "../lib/cs225/png.h"

/**
* @brief Plots all vertices (and edges if specified) of a graph onto a plate carrée map projection
* Warning: this may look very messy
*
* @param worldMap The blank plate carrée map projection to use
* @param g The graph to plot
* @param edges Whether to also plot the edges
* @param showProgress Whether to show a progress bar for the edges (only matters of edges is true)
* @param pointSize The radius of the points, in pixels
* @param lineThickness The thickness of the lines, in pixels
* @param pointPixel The pixel to be used to fill the points (red by default)
* @param linePixel The pixel to be used to fill the lines (orange by default)
* @return PNG The map png
*/
cs225::PNG plotGraph(cs225::PNG worldMap, Graph g, bool edges, bool showProgress = true, double pointSize = 4,
    int lineThickness = 1, cs225::HSLAPixel pointPixel = cs225::HSLAPixel(0, 1, 0.5, 1),
    cs225::HSLAPixel linePixel = cs225::HSLAPixel(20, 1, 0.5, 1));

/**
* @brief Plots the Dijkstra path onto a plate carrée map projection
*
* @param worldMap The blank plate carrée map projection to use
* @param g The graph on which to apply Dijkstra
* @param source The source airport ID
* @param target The target airport ID
* @param pointSize The radius of the points, in pixels
* @param lineThickness The thickness of the lines, in pixels
* @param pointPixel The pixel to be used to fill the points (red by default)
* @param linePixel The pixel to be used to fill the lines (orange by default)
* @return PNG The map png
*/
cs225::PNG plotDijkstra(cs225::PNG worldMap, Graph g, int source, int target, double pointSize = 6, int lineThickness = 4, 
    cs225::HSLAPixel pointPixel = cs225::HSLAPixel(0, 1, 0.5, 1),
    cs225::HSLAPixel linePixel = cs225::HSLAPixel(20, 1, 0.5, 1));

/**
* @brief Plots the BFS traversal on a plate carrée map projection
* Warning: this may look very messy
*
* @param worldMap The blank plate carrée map projection to use
* @param g The graph on which to apply BFS
* @param start The start of the BFS algorithm
* @param pointSize The radius of the points, in pixels
* @param lineThickness The thickness of the lines, in pixels
* @param pointPixel The pixel to be used to fill the points (red by default)
* @param linePixel The pixel to be used to fill the lines (orange by default)
* @return PNG The map png
*/
cs225::PNG plotBFS(cs225::PNG worldMap, Graph g, int start, double pointSize = 6, int lineThickness = 2,
    cs225::HSLAPixel pointPixel = cs225::HSLAPixel(0, 1, 0.5, 1),
    cs225::HSLAPixel linePixel = cs225::HSLAPixel(20, 1, 0.5, 1));

/**
* @brief Plots each airport on a plate carrée map projection
* The size of the point is proportional to its betweenness centrality
* (can be determined probabilistically, see sampleSize)
*
* @param worldMap The blank plate carrée map projection to use
* @param g The graph on which to apply betweenness centrality
* @param showProgress Whether to show a progress bar
* @param sampleSize How many paths to sample from the graph; if 0, the non-probabilistic method will be used
* @param skipNonPaths Whether or not to skip pairs of points with no path (if using probabilistic methods)
* @param maxRadius The maximum radius of the points (the most central point will have this radius)
* @param pointPixel The pixel to be used to fill the points (red by default)
* @return PNG The map png
*/
cs225::PNG plotBetweenness(cs225::PNG worldMap, Graph g, bool showProgress = true, int sampleSize = 0, bool skipNonPaths = true, double maxRadius = 10,
    cs225::HSLAPixel pointPixel = cs225::HSLAPixel(0, 1, 0.5, 1));

/**
* @brief Plots a path on a world map
* The path is given as a vector of IDs
* 
* @param worldMap The map to plot the path on
* @param g The graph the path is on
* @param path The path of IDs to plot
* @param pointSize The radius of the points
* @param lineThickness The radius of the lines
* @param pointPixel The pixel to be used to fill the points
* @param linePixel The pixel to be used to fill the lines
*/
void plotPath(cs225::PNG & worldMap, Graph g, vector<int> path, double pointSize, int lineThickness,
    cs225::HSLAPixel pointPixel, cs225::HSLAPixel linePixel);

/**
* @brief Plots a point on a map at a given latitude and longitude
*
* @param worldMap The map to plot the point on
* @param lat The point's latitude
* @param lon The point's longitude
* @param radius The radius of the point
* @param pixel The pixel to be used to fill the point
*/
void plotPoint(cs225::PNG & worldMap, double lat, double lon, double radius, cs225::HSLAPixel pixel);

/**
* @brief Plots a line on a map between two points
* Uses Bresenham's line algorithm
* Makes the line thicker along axis where it is most noticable
*
* @param worldMap The map to plot the line on
* @param lat1 The latitude of the first point
* @param lon1 The longitude of the first point
* @param lat2 The latitude of the second point
* @param lon2 The longitude of the second point
* @param thickness The thickness of the line in pixels
* @param pixel The pixel to be used to fill the line
*/
void plotLine(cs225::PNG & worldMap, double lat1, double lon1, double lat2, double lon2, int thickness,
    cs225::HSLAPixel pixel);
