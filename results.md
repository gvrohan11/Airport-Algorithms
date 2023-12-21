# Written Report

## Graph class <br>
Our main data structure, the graph, is directed and weighted by distance. The vertices are the airports and the edges are the connections (one-way). For time and space complexity, we denote these as V and E, respectively. The graph is ID-based, storing an unordered map of an integer ID to its GraphNode, which contains all pertinent information about an airport: the latitude, longitude, name, and an unordered map of connections which maps a connected airport’s ID to the distance.

The graph can add an airport, add a connection, remove a connection (disconnect), get the distance between two airports (infinity if not connected), get the total number of airports or connections, determine if an airport is in the graph, determine if two airports are connected, and access airport information in O(1) (average case). A node v can be removed in O(|V| + deg(v)). If not sorted, a list of all airports can be obtained in O(|V|), and a list of all connections from a vertex v can be obtained in O(deg(v)). If specified to be sorted, the time complexities are O(|V|log(|V|)) and O(deg(v)log(deg(v))), respectively. The space complexity of the graph is O(|V| + |E|).

The distance between two airports can be calculated in one of two ways, as specified in the constructor or changed later on. The first way is to account for the curvature of the Earth and use the Haversine formula to calculate the distance given the longitude and latitude. The second way is to calculate the distance as if the airports were on a 2D plane, which is useful for testing artificial examples but not accurate to our dataset.

For testing, all functions were considered, including adding/removing airports/connection, and calculating distance in both ways. When using our dataset, the distance between two airports was looked up ahead of time, and a 2% margin of error was allowed due to the slight ellipticity of the Earth.

## readdat functions <br>
To read our .dat files, a number of functions were created to parse lines with delimiter-separated values, check the validity of the data, and read the data into a graph. The function readData takes in a file of vertices, a file of edges, and returns the resulting graph. An optional argument takes a vector of IDs, and if used, only those IDs will be considered. The function sampleData also takes in two files along with a sampleSize. That many IDs, chosen randomly, will be read into a graph and returned.

Tests were performed for all functions, including different delimiters, the use of quotes in the line, and a sampleSize of more than the number of IDs in the data (which has the same result as normal readData).


## Dijktra’s Algorithm <br>
Given a weighted or unweighted set of data in the format of graph data structure, this algorithm will essentially find the shortest path between two points. The algorithm’s time complexity is `O(|V| + |E|log|V|)`, and the space complexity is O(|E| + |V|). 

In the case of this project, Dijkstra’s Algorithm was encapsulated as class `Dijkstras`, in which each instance of a `Dijkstras` represents the algorithm’s traversal. The specific function that used the algorithm’s implementation is `vector<int> getPath(const Graph& g, int source, int target)`, in which the function takes in a `Graph` containing the airport network, an `int` ID of the source airport, and `int` ID of the destination airport. With input, the function returns a `vector<int>` of airport IDs required to visit on the shortest path from `int` source to `int` destination; however, if no path is possible, the function will return `vector<int>()` empty vector.

The algorithm itself was adapted from pseudocode taken from a research journal; however, minor modifications had to be made to suit some of the accessibility of the `Dijkstras` class. 

For example, `vector<int> airports_` was created as a private variable to maintain a list of all airports. `map<int, double> ports_` was created to track the source airport’s neighbors to their distances. Additionally, `map<int, int> prev_` mapped each airport’s immediately previous source. Lastly, `double shortestDistance_` was created to store the shortest distance, which was calculated in `vector<int> getPath(const Graph& g, int source, int target)`; subsequently, a `double shortestDistance()` was a function designed to retrieve its respective private variable.

To achieve the desired time and space complexity, `vector<int> getPath(const Graph& g, int source, int target)` made use of a modified version `std::priority_queue`, which essentially maintains a min heap through a passed in lambda function that serves as comparator. The implementation of this container adaptor was critical in achieving better run time.

To test Dijkstra’s Algorithm, two types of test cases were created. One type of test case dealt with creating arbitrary nodes with arbitrary IDs and coordinates to test `Graph` functionality and `Dijkstras` functionality. The other type of test cases were ones that used the airport network, in which real airport IDs are used as inputs to generate the expected output. For example, as a sample, one of the test cases tests if the shortest path from Champaign, Illinois “CMI” to Chicago, Illinois “ORD”. The expected shortest path for this journey would be a single direct flight, in which we would expect a vector containing simply the integer IDs for CMI and ORD, exclusively in that order. In a more complex path, a test ran between an airport in Greenland to Kenya. The output is depicted is as the following: 

<img width="252" alt="Screen Shot 2022-12-12 at 3 44 52 PM" src="https://user-images.githubusercontent.com/71199424/207161305-e9363553-1077-48c4-bf35-4f60925f3c4f.png">


## Breadth-First Search <br>

Breadth-First Search is an algorithm that traverses nodes at each level before increasing the depth. When initially deciding on its application to our project, we decided that it will accept a graph in the form of an adjacency list and output a list of all airports visited in a particular order. The run time of BFS was `O(|V| + |E|)` and the space complexity was bounded at `O(|V|^2)`.

Similar to Dijkstra’s Algorithm, BFS was contained in class `BFS`. The function that used BFS’s implementation was `vector<int> traversalOfBFS(const Graph& g, int startID)`, which took in a graph of the airport networks, and a starting airport ID. As a result, the output is a vector of all ids visited from the airport in the order that they are visited. The pseudocode that was used to generate this function was adapted from CS225 lecture notes. The use of this function allows one to see all possible destinations from a given airport.

<img width="372" alt="Screen Shot 2022-12-12 at 3 46 51 PM" src="https://user-images.githubusercontent.com/71199424/207161622-7fd29f51-6151-4eb1-8089-dc64e02ecb6c.png">


## Betweenness Centrality <br>

Given the airport data structured as a weighted and directed graph, The Betweenness Centrality algorithm was able to detect which airports had a higher betweenness centrality score, or in other words had the most connections. For every pair of airports A and B, this algorithm took the shortest path between them and counted the number of times an airport that is neither A nor B appeared in the path, and a higher count meant that an airport was considered a “hub”. We outputted the results from the betweenness centrality algorithm in an std::map, where the airport ID’s represented the keys and the scores represented the values. A visual representation with size of dots representing airports proportional to their betweenness scores is shown below.

<img width="370" alt="betcent_example" src="https://user-images.githubusercontent.com/71199424/207157358-245d142c-6ad1-44a8-81f3-a72e6423a715.png">

Because the graph was weighted and directed, we used Dijkstra’s algorithm to get the shortest paths. This ultimately ended up in a run time of O((|V|^2) * (|E| + |V|log|V|)), which would be really slow. Therefore, we decided to implement a probabilistic approach which sampled K airports and computed the betweenness score for those K airports. This approach was beneficial because it take less time and the random sample was a good representation of the dataset. The run time of this algorithm was O(K * (|E| + |V|log|V|)).

For testing, we first created our own simple graphs, complex graphs, and disconnected graphs apart from the data set and tested the non-probabilistic method. So for example for the simple graph, we added 4 points in a straight line and made sure the betweeness score of each point was equal to what we expected of it. For the complex graph, we added multiple nodes with multiple edges, but we were still able to manually calculate the betweeness score of each node and compare it to what the function outputted. And the same process applied to the disconnected graph, but not every pair of points had a path, and the dijkstra algorithm accounted for this. 

For the probabilistic function, we used the airport data set and passed in (parameter) a number of airports to test. Because there was a random output of airports, we made sure to test that the output std::map had a size <= the number of airports to test.

Finally, we also included another function to create a set of airports with a minimum betweeness centrality score. This was beneficial to separate popular airports (higher scores) from unpopular airports (lower scores). For testing, we used the same graphs and maps that we used to test the betweeness methods and used those to output sets of airports that had a betweeness score and compared them to what we expected the set to contain and not contain `(set.find(x) != or == set.end())`.

## makeimage functions <br>

The makeimage functions are used to visualize the graph and its algorithms on a map projection. Because latitude and longitude are given, a plate carrée projection is used, as shown in the maps above. There are four main functions: one to plot Dijkstra’s algorithm, breadth-first search, betweenness centrality, and the graph in general. The last one simply plots the airports on a graph, with or without edges. A plot with edges is shown below on a subset of the airports:

<img width="364" alt="Screen Shot 2022-12-12 at 3 48 25 PM" src="https://user-images.githubusercontent.com/71199424/207162003-3fceff29-7fce-4308-a6d8-6672a95a6ede.png">

To draw the lines, Bresenham's line algorithm with the extension to support all slopes was used. The color of the points and lines, was well as the radius and thickness, respectively, can be specified. For example, here is a customized Dijkstra’s algorithm output:

<img width="431" alt="Screen Shot 2022-12-12 at 3 48 57 PM" src="https://user-images.githubusercontent.com/71199424/207162334-bac2227b-0ffc-4f61-b3c5-3d9b85d058f5.png">

One assumption that the functions make is that a line never wraps around the map projection. While this is not always true in real life, the routes dataset doesn’t specify whether the flight goes east or west, and so we assumed the direction that makes plotting simplest.

Tests were conducted similarly to those on image-related MPs: a folder was created to hold all “expected” images, and the generated images were compared to their respective expected image. Expected images were checked beforehand for validity.

## Reflection on Project <br>

Our objective and question of interest when taking on the CS225 final project was to find an effective way to model the global network of airports using the tools we learned in class. With a graphical representation of an airport network, we wanted to gauge specific metrics, such as shortest distances between airports, the number of stops in a certain journey, and the popularity of airports. The utilization of a graph data structure for this problem was essential, and it allowed us to develop algorithms that traversed the network for the metrics we intended to extract. For example, with a breadth-first search, we determined which airports were reachable from a given one and revealed that many airports had no connections. More importantly, our visualization implementations allowed us to see these algorithms’ output on the world map. Through these methods, we were able to gain a deeper understanding of the dataset and the data structure and algorithms as a whole.
