#include "readdat.h"
#include <iostream>
#include <random>
#include <map>

using namespace std;

vector<string> readline(stringstream & ss, char delim) {
    vector<string> fields;
    string field = "";
    char c;
    //this is needed so commas in quotes aren't used
    bool inQuote = false;
    while (ss.get(c)) {
        if (c == '"') {
            //quote either starts or ends when a " is found
            inQuote = !inQuote;
        } else if (c == delim && !inQuote) {
            //adds the field to the list
            fields.push_back(field);
            //gets started on the new field
            field = "";
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    return fields;
}

bool validID(int id) {
    return id > 0;
}

bool validIATA(string iata) {
    for (char c : iata) {
        if (!isalpha(c)) {
            return false;
        }
        if (!isupper(c)) {
            return false;
        }
    }
    return iata.length() == 3;
}

bool validLatitude(double latitude) {
    return latitude >= -90 && latitude <= 90;
}

bool validLongitude(double longitude) {
    return longitude >= -180 && longitude <= 180;
}

Graph readData(string vertexFile, string edgeFile, vector<int> ids) {
    bool idsGiven = !ids.empty();
    Graph g;
    ifstream airports(vertexFile);
    ifstream routes(edgeFile);
    string line;
    //map from IATA to ID to fix issues later on
    map<string, int> iataToID;

    //reads in the airports
    while (getline(airports, line)) {
        stringstream ss(line);
        vector<string> fields = readline(ss);
        //skip if there are not 14 fields
        if (fields.size() != 14) {
            continue;
        }
        //we only care about these fields
        int id = stoi(fields[0]);
        string name = fields[1];
        string iata = fields[4];
        double latitude = stod(fields[6]);
        double longitude = stod(fields[7]);
        if (validID(id) && validIATA(iata)) {
            iataToID[iata] = id;
        }

        if (validID(id) && validLatitude(latitude) && validLongitude(longitude)) {
            //add the airport to the graph (if appropriate)
            if (idsGiven) {
                // check if the ID is in the list
                for (int givenID : ids) {
                    if (id == givenID) {
                        g.addNode(id, name, latitude, longitude);
                        break;
                    }
                }
            } else {
                g.addNode(id, name, latitude, longitude);
            }
        }
    }
    airports.close();

    //reads in the connections
    while (getline(routes, line)) {
        stringstream ss(line);
        vector<string> fields = readline(ss);
        //skip if there aren't 9 lines
        if (fields.size() != 9) {
            continue;
        }
        int id1, id2;
        //the ID will be missing occassionally so we try to use the IATA to figure it out
        //this is for the first airport
        if (fields[3] == "\\N") {
            if (iataToID.find(fields[2]) != iataToID.end()) {
                //if the IATA is found use the corresponding ID
                id1 = iataToID[fields[2]];
            } else {
                //skip it otherwise
                continue;
            }
        } else {
            id1 = stoi(fields[3]);
        }
        //same thing for the second airport
        if (fields[5] == "\\N") {
            if (iataToID.find(fields[4]) != iataToID.end()) {
                id2 = iataToID[fields[4]];
            } else {
                continue;
            }
        } else {
            id2 = stoi(fields[5]);
        }
        if (!(validID(id1) && validID(id2))) {
            continue;
        }
        if (g.inGraph(id1) && g.inGraph(id2)) {
            g.connect(id1, id2);
        }   
    }
    routes.close();

    return g;
}

Graph sampleData(string vertexFile, string edgeFile, int sampleSize) {
    // used to keep track of read-in data before sampling from it
    struct airport {
        int id_;
        string name_, iata_;
        double latitude_, longitude_;
        airport(int id, string name, string iata, double latitude, double longitude) :
            id_(id), name_(name), iata_(iata), latitude_(latitude), longitude_(longitude) {}
    };
    Graph g;
    ifstream airports(vertexFile);
    ifstream routes(edgeFile);
    string line;
    //map from IATA to ID to fix issues later on
    map<string, int> iataToID;
    // possible airports to sample from
    vector<airport> airportList;

    //reads in the airports
    while (getline(airports, line)) {
        stringstream ss(line);
        vector<string> fields = readline(ss);
        //skip if there are not 14 fields
        if (fields.size() != 14) {
            continue;
        }
        //we only care about these fields
        int id = stoi(fields[0]);
        string name = fields[1];
        string iata = fields[4];
        double latitude = stod(fields[6]);
        double longitude = stod(fields[7]);
        airportList.push_back(airport(id, name, iata, latitude, longitude));
        /*
        if (validID(id) && validIATA(iata)) {
            iataToID[iata] = id;
        }

        if (validID(id) && validLatitude(latitude) && validLongitude(longitude)) {
            //add the airport to the graph
            g.addNode(id, name, latitude, longitude);
        }
        */
    }
    airports.close();

    // sample
    if (sampleSize > (int)airportList.size()) {
        sampleSize = airportList.size();
    }
    default_random_engine generator;
    for (int i = 0; i < sampleSize; i++) {
        uniform_int_distribution<int> distribution(0, airportList.size() - 1);
        int index = distribution(generator);
        airport a = airportList[index];
        if (validID(a.id_) && validIATA(a.iata_)) {
            iataToID[a.iata_] = a.id_;
        }
        if (validID(a.id_) && validLatitude(a.latitude_) && validLongitude(a.longitude_)) {
            //add the airport to the graph
            g.addNode(a.id_, a.name_, a.latitude_, a.longitude_);
        }
        airportList.erase(airportList.begin() + index);
    }

    //reads in the connections
    while (getline(routes, line)) {
        stringstream ss(line);
        vector<string> fields = readline(ss);
        //skip if there aren't 9 lines
        if (fields.size() != 9) {
            continue;
        }
        int id1, id2;
        //the ID will be missing occassionally so we try to use the IATA to figure it out
        //this is for the first airport
        if (fields[3] == "\\N") {
            if (iataToID.find(fields[2]) != iataToID.end()) {
                //if the IATA is found use the corresponding ID
                id1 = iataToID[fields[2]];
            } else {
                //skip it otherwise
                continue;
            }
        } else {
            id1 = stoi(fields[3]);
        }
        //same thing for the second airport
        if (fields[5] == "\\N") {
            if (iataToID.find(fields[4]) != iataToID.end()) {
                id2 = iataToID[fields[4]];
            } else {
                continue;
            }
        } else {
            id2 = stoi(fields[5]);
        }
        if (!(validID(id1) && validID(id2))) {
            continue;
        }
        if (g.inGraph(id1) && g.inGraph(id2)) {
            g.connect(id1, id2);
        }   
    }
    routes.close();

    return g;
}
