#ifndef FLIGHTGRAPH_H
#define FLIGHTGRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Cache.h"

using namespace std;

class FlightGraph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList; // ✅ Stores the flight network
    LRUCache cache; // ✅ LRU Cache for optimized searches

public:
    FlightGraph(int cacheSize = 3); // ✅ Constructor initializes the cache with a default size of 3

    // ✅ Adds a flight
    void addFlight(const string &source, const string &destination, int cost);

    // ✅ Finds the shortest path using Dijkstra’s Algorithm
    vector<string> findShortestPath(const string &start, const string &end);

    // ✅ Displays the flight network (Newly Added!)
    void displayFlights() const;

    // ✅ LRU Cache Methods
    vector<string> getCachedPath(const string &start, const string &destination);
    void storeInCache(const string &start, const string &destination, const vector<string> &path);
};

// ✅ Declare helper functions (Fix for undefined errors)
string trim(const string &str);
string toLowerCase(const string &str);

#endif // FLIGHTGRAPH_H
