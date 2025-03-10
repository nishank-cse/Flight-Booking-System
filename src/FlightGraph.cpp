#include "FlightGraph.h"
#include <queue>
#include <limits>
#include <climits>
#include <algorithm>
#include <cctype>
#include <iostream>

// ✅ Trim spaces from a string
string trim(const string &str) {
    string result = str;
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](unsigned char ch) { return !isspace(ch); }));
    result.erase(find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), result.end());
    return result;
}

// ✅ Convert a string to lowercase
string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// ✅ Constructor: Initializes FlightGraph with LRU Cache
FlightGraph::FlightGraph(int cacheSize) : cache(cacheSize) {}

// ✅ Adds a flight connection
void FlightGraph::addFlight(const string &source, const string &destination, int cost) {
    string trimmedSource = toLowerCase(trim(source));
    string trimmedDestination = toLowerCase(trim(destination));

    adjList[trimmedSource].push_back({trimmedDestination, cost});
    adjList[trimmedDestination].push_back({trimmedSource, cost}); // Assuming a bidirectional flight
}

// ✅ Finds the shortest path (Uses LRU Cache)
vector<string> FlightGraph::findShortestPath(const string &start, const string &end) {
    string trimmedStart = toLowerCase(trim(start));
    string trimmedEnd = toLowerCase(trim(end));

    // ✅ Check Cache First (🔄 Optimized Search)
    vector<string> cachedResult = cache.getSearchResult(trimmedStart, trimmedEnd);
    if (!cachedResult.empty()) {
        cout << "🔄 Cache Hit! Optimized Search Result.\n";
        return cachedResult;
    }

    // ❌ Check if both cities exist
    if (adjList.find(trimmedStart) == adjList.end() || adjList.find(trimmedEnd) == adjList.end()) {
        cout << "❌ Error: '" << start << "' or '" << end << "' not found in the flight network.\n";
        return {};
    }

    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    // ✅ Initialize distances
    for (auto &city : adjList) {
        dist[city.first] = INT_MAX;
    }
    dist[trimmedStart] = 0;
    pq.push({0, trimmedStart});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        string current = pq.top().second;
        pq.pop();

        if (current == trimmedEnd) break; // Reached destination

        for (auto &neighborPair : adjList[current]) {
            string neighbor = neighborPair.first;
            int weight = neighborPair.second;

            int newDist = currentDist + weight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    // ❌ Check if destination is unreachable
    if (prev.find(trimmedEnd) == prev.end() && trimmedEnd != trimmedStart) {
        cout << "❌ Error: No valid flight path found from " << start << " to " << end << ".\n";
        return {};
    }

    // ✅ Reconstruct the shortest path
    vector<string> path;
    string at = trimmedEnd;
    while (!at.empty()) {
        path.push_back(at);
        at = prev[at];
    }
    reverse(path.begin(), path.end());

    // ✅ Store the result in cache
    cache.putSearchResult(trimmedStart, trimmedEnd, path);

    return path;
}

// ✅ Displays the flight network (Newly Added!)
void FlightGraph::displayFlights() const {
    cout << "✈️ Flight Network:\n";
    for (const auto &city : adjList) {
        cout << "🛫 " << city.first << " -> ";
        for (const auto &dest : city.second) {
            cout << dest.first << " (₹" << dest.second << "), ";
        }
        cout << "\n";
    }
}

// ✅ Fetch cached search result
vector<string> FlightGraph::getCachedPath(const string &start, const string &destination) {
    return cache.getSearchResult(toLowerCase(trim(start)), toLowerCase(trim(destination)));
}

// ✅ Store computed search result in cache
void FlightGraph::storeInCache(const string &start, const string &destination, const vector<string> &path) {
    cache.putSearchResult(toLowerCase(trim(start)), toLowerCase(trim(destination)), path);
}
