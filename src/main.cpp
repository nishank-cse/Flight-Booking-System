#include "FlightGraph.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    FlightGraph flightSystem(5); // ✅ Initialize FlightGraph with LRU Cache of size 5

    // 🛫 Adding Flights
    flightSystem.addFlight("New York", "London", 500);
    flightSystem.addFlight("London", "Paris", 200);
    flightSystem.addFlight("New York", "Dubai", 700);
    flightSystem.addFlight("Dubai", "Paris", 300);

    string start, destination;

    while (true) {
        // ✅ Get departure city with validation
        cout << "\nEnter departure city (or 'exit' to quit): ";
        getline(cin, start);
        if (start.empty()) {
            cout << "ERROR: Departure city cannot be empty. Try again.\n";
            continue;
        }
        if (start == "exit") break;

        // ✅ Get destination city with validation
        cout << "Enter destination city: ";
        getline(cin, destination);
        if (destination.empty()) {
            cout << "ERROR: Destination city cannot be empty. Try again.\n";
            continue;
        }

        // ✅ Convert input to lowercase for case-insensitive search
        transform(start.begin(), start.end(), start.begin(), ::tolower);
        transform(destination.begin(), destination.end(), destination.begin(), ::tolower);

        // ✅ First, Check LRU Cache
        vector<string> cachedPath = flightSystem.getCachedPath(start, destination);
        if (!cachedPath.empty()) {
            cout << "CACHE HIT! Optimized Search:\nShortest Path: ";
            for (const auto &city : cachedPath)
                cout << city << " -> ";
            cout << "END\n";
            continue;
        }

        // ✅ Compute Shortest Path if not in Cache
        vector<string> path = flightSystem.findShortestPath(start, destination);
        if (path.empty()) {
            cout << "ERROR: No valid flight path found. Please check city names and try again.\n";
            continue;
        }

        // ✅ Store the Result in Cache
        flightSystem.storeInCache(start, destination, path);

        // ✈️ Display Flight Path
        cout << "Shortest Path: ";
        for (const auto &city : path)
            cout << city << " -> ";
        cout << "END\n";
    }

    cout << "Program exited successfully.\n";
    return 0;
}
