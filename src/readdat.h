#pragma once
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// These functions are used for reading in data from .dat files

/**
 * @brief Gets each field in a line separated by a delimiter
 * 
 * @param ss A stringstream with the line
 * @param delim The delimiter, comma by default
 * @return vector<string> A vector with each item being a field in the line
 */
std::vector<std::string> readline(std::stringstream & ss, char delim = ',');

/**
 * @brief Determines if an ID is valid (i.e. greater than 0)
 * 
 * @param id the ID
 * @return bool Whether the ID is valid
 */
bool validID(int id);
/**
 * @brief Determines if an International Air Transport Association code is valid
 * The IATA code is valid if it consists of three capital letters
 * 
 * @param iata the IATA code
 * @return bool Whether the IATA code is valid
 */
bool validIATA(std::string iata);
/**
 * @brief Determines if a latitude is valid (i.e. no more than 90 in absolute value)
 * 
 * @param latitude the latitude
 * @return bool Whether the latitude is valid
 */
bool validLatitude(double latitude);
/**
 * @brief Determines if a longitude is valid (i.e. no more than 180 in absolute value)
 * 
 * @param latitude the longitude
 * @return bool Whether the longitude is valid
 */
bool validLongitude(double longitude);

/**
* @brief Reads in data to a Graph
* If a vector of IDs is given, only those IDs will be used
* This function assumes that the data fields are formatted like on https://openflights.org/data.html
* Where the vertex file is formatted like airports.dat, and the edges, like routes.dat
*
* @param vertexFile A file of the graph vertices
* @param edgeFile A file of the graph edges
* @param ids A vector of the IDs to add (if empty, all IDs found will be used)
* @return Graph A graph of the data
*/
Graph readData(std::string vertexFile, std::string edgeFile, std::vector<int> ids = std::vector<int>());

/**
* @brief Reads in data to a Graph
* Only a certain amount of lines will be used, chosen randomly (uniformly)
* If the sample size is greater than the number of vertices, the number of vertices is used
*
* @param vertexFile A file of the graph vertices
* @param edgeFile A file of the graph edges
* @param sampleSize The number of lines that will 
* @return Graph A graph of the data
*/
Graph sampleData(std::string vertexFile, std::string edgeFile, int sampleSize);
