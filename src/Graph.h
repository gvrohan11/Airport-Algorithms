#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>
#include <limits>

/**
 * @brief Stores all airports and their connections
 * This Graph is directional and stores distances
 */
class Graph {
private:
    /**
    * @brief Stores the data of an airport and its connections
    */
    struct GraphNode {
        std::string name_; // The airport's name
        double latitude_, longitude_; // The airport's longitude and latitude

        std::unordered_map<int, double> connections_; // A map between the connection's ID and distance
        /**
        * @brief Construct a GraphNode with default parameters
        */
        GraphNode() : name_(""), latitude_(0), longitude_(0) {}
        /**
         * @brief Constructs a new GraphNode object with the given specifications
         * 
         * @param name The name of the airport
         * @param lat The latitude of the airport
         * @param long The longitude of the airport
         */
        GraphNode(std::string name, double lat, double lon) :
            name_(name), latitude_(lat), longitude_(lon) {}
        /**
        * @brief Determines if this GraphNode is connected to another.
        *
        * @param id The ID to see if it's connected to
        * @return bool Whether there is a connection
        */
        bool _connectedTo(int id) const { return connections_.find(id) != connections_.end(); }
        /**
        * @brief Gets the connection distance between this and an ID
        * If not connected returns infinity
        *
        * @param id The ID it's connected to
        */
        double _connectionDistance(int id) const;
    };

public:
    /**
     * @brief Constructs a new Graph object with no airports or connections
     *
     * @param spherical Whether the distance calculation should be done on a sphere or 2D plane
     */
    Graph(bool spherical = true) : spherical_(spherical), numConnections_(0) {}
    /**
    * @brief Getter for the spherical property
    *
    * @return bool Whether the distance calculation should be done on a sphere or 2D plane
    */
    bool getSpherical() { return spherical_; }
    /**
    * @brief Setter for the spherical property
    *
    * @param spherical Whether the distance calculation should be done on a sphere or 2D plane
    */
    void setSpherical(bool spherical) { spherical_ = spherical; } 
    /**
     * @brief Adds an airport to the graph without any connections
     * 
     * @param id the unique idenifying number of the airport
     * @param name the airport name
     * @param latitude the airport's latitude
     * @param longitude the airport's longitude
     */
    void addNode(int id, std::string name, double latitude, double longitude);
    /**
    * @brief Removes a node and all its connections
    *
    * @param id The airport ID to remove (must be in graph)
    */
    void removeNode(int id);
    /**
     * @brief Makes a connection from one airport to another (does not go both ways)
     * 
     * @param id1 The ID of the starting airport (must be in graph)
     * @param id2 The ID of the ending airport (must be in graph)
     */
    void connect(int id1, int id2);
    /**
     * @brief Removes a connection from one airport to another (does not go both ways)
     * The airports must be connected in the first place
     * 
     * @param id1 The ID of the starting airport (must be in graph)
     * @param id2 The ID of the ending airport (must be in graph)
     */
    void disconnect(int id1, int id2);
    /**
     * @brief Gets the number of airports in the graph
     * 
     * @return int The number of airports in the graph
     */
    int size() const { return nodes_.size(); }
    /**
     * @brief Gets the number of connections in the graph (one-directional)
     * 
     * @return int The number of connections in the graph
     */
    int connections() const { return numConnections_; }
    /**
     * @brief Gets the IDs of all airports that were added
     * 
     * @param sorted Whether to sort the IDs
     * @return vector<int> A vector contains all airport IDs
     */
    std::vector<int> getIDs(bool sorted = true) const; 
    /**
    * @brief Determines if the the first airport is connected to the second
    *
    * @param id1 The first airport's ID (must be in graph)
    * @param id2 The second airport's ID (must be in graph)
    * @return bool Whether there is a connection
    */
    bool connectedTo(int id1, int id2) const;
    /**
    * @brief Gets the distance of the connection between two airports
    * (directional, from the first to the second)
    * If not connected returns infinity
    *
    * @param id1 The first airport's ID (must be in graph)
    * @param id2 The second airport's ID (must be in graph)
    * @return double The weight
    */
    double getDistance(int id1, int id2) const { 
        if (id1 == id2) { return 0; }
        return nodes_.at(id1)._connectionDistance(id2);
    }

    /**
    * @brief Gets all connections of an airport (one-way, starting from the given airport)
    *
    * @param id The airport's ID
    * @param sorted Whether to sort the IDs
    * @return vector<int> The list of connections
    */
    std::vector<int> getConnections(int id, bool sorted = true) const;

    /**
    * @brief: Gets the name of an airport from its ID
    *
    * @param id The airport's ID
    * @return string The airport's name
    */
    std::string getName(int id) const { return nodes_.at(id).name_; }
    /**
    * @brief: Gets the latitude of an airport from its ID
    *
    * @param id The airport's ID
    * @return string The airport's latitude
    */
    double getLatitude(int id) const { return nodes_.at(id).latitude_; }
    /**
    * @brief: Gets the longitude of an airport from its ID
    *
    * @param id The airport's ID
    * @return string The airport's longitude
    */
    double getLongitude(int id) const { return nodes_.at(id).longitude_; }

    /**
    * @brief Checks if an ID is in the graph
    *
    * @param id The airport's ID
    * @return bool Whether the ID is in the graph
    */
    bool inGraph(int id) const { return nodes_.find(id) != nodes_.end(); }

private:
    bool spherical_; // Whether the distance calculation should be done on a sphere or 2D plane
    int numConnections_; // Stores the number of connections made in the grap
    std::unordered_map<int, GraphNode> nodes_; // Maps each airport's ID to its GraphNode
    /**
     * @brief Calculates the great circle distance between two airports using the haversine formula
     * This technically assumes the Earth is a sphere but is easier to calculate
     *
     * @param a the first airport's ID
     * @param b the second airport's ID
     * @return double The distance between the airports, accounting for the Earth's curvature
    */
    double _distance(int id1, int id2) const;
};
