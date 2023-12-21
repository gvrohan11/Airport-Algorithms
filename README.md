# Airport Algorithms - CS 225 Data Structures Final Project (Fall 2022)

## Developers: Rohan Gudipaty, Tyler Hecht, Will Otani, Swaroop Thammineni


## Project Summary

In this project we designed multiple algorithms and visualization tools implemented on the network of world airports. Using a dataset retrieved from OpenFlights database, the airport network was constructed using all possible routes for the 10,000 airports across the world as of 2017. Furthermore, our algorithms will provide an in-depth exploration of optimal routes from sources and destinations as well as centrality of various airports. In addition, with visualization tools using cs225's PNG library, it allows for dynamic visualation of airport networks.  

Video: https://www.youtube.com/watch?v=ZVbzeZWpgCo

## Code File Structure
* Build
* Data : contains airport data and routes data necessary for processing
    * airports.dat : airports info
    * map.png : world map basis
    * routes.dat : routes info
* entry
    * main.cpp : Where you can try out the algorithms yourself
* lib : cs225 color space
* src
    * Algorithms
        * dijkstra : Dijkstra's Algorithm for shortest path between two airports
            * dijkstra.cpp
            * dijkstra.h
        * bfs : Breadth-First Search Algorithm traverses every single pathway from a given airport
            * bfs.cpp
            * bfs.h
        * bet_cent : Determines the "popularity" of airports by how often they appear a shortest path
            * bet_cent.cpp
            * bet_cent.h
        * makeimage : Plots points and lines on a map to visualize data and algorithms
            * makeimage.cpp
            * makeimage.h
    * CMakeLists.txt
    * Graph.cpp
    * Graph.h
    * ProgressBar.cpp
    * ProgressBar.h
    * readdat.cpp
    * readdat.h
        
* readdat : Reads data from files and creates graphs from it
* Graph : A class to represent a network of airports
* ProgressBar : For showing progress on the command line
* tests : runs test cases
* Dockerfile : cs225 Dockerfile is used
* CMakeLists.txt : CMake configuration
* README.md : What you're reading right now!
* results.md : A report explaining our goals and algorithms

## File Interaction

The `readdat` functions read in data to construct a `Graph` network of airports. The algorithm classes utilize instances of `Graph` to operate on with respective traversals. The `makeimage` functions use the other algorithms and to visualize them on a map.


## Set Up
Clone the repository:
```
git clone [REPOSITORY URL]
cd [REPOSITORY NAME]
````
Create a build directory and use cmake to create a makefile:
```
mkdir build
cd build
cmake ..
```

Create and run executable:
```
make main
./main
```

Testing:
* For specifics test follow ./test with the test name
```
make test
./test
```

## How to Generate Visualization
1) Read in datasets to graph in `entry/main.cpp`
2) Use functions from `makeimage`to generate a plot of the Graph, Dijkstra, Centrality or Betweenness. 
3) Call function in `entry/main.cpp` and write to a file.


## Bibliography
https://openflights.org/data.html#license

