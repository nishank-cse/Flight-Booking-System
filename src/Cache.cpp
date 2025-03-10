#include "Cache.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// ✅ Helper Function: Generate a Unique Cache Key
string LRUCache::generateKey(const string &start, const string &destination) {
    return start + "->" + destination;
}

// ✅ Constructor: Initializes Cache with a given size
LRUCache::LRUCache(int size) : capacity(size) {}

// ✅ Get search result from cache
vector<string> LRUCache::getSearchResult(const string &start, const string &destination) {
    string key = generateKey(start, destination);

    // 🔎 Check if search result is cached
    if (cache.find(key) == cache.end()) {
        return {}; // ❌ Not Found
    }

    // ✅ Move the accessed search result to the front (Most Recently Used)
    recentSearches.splice(recentSearches.begin(), recentSearches, cache[key].second);

    // ✅ Parse stored search result into vector format
    vector<string> result;
    stringstream ss(cache[key].first);
    string city;
    while (getline(ss, city, ',')) {
        result.push_back(city);
    }
    return result;
}

// ✅ Store new search result in cache
void LRUCache::putSearchResult(const string &start, const string &destination, const vector<string> &path) {
    string key = generateKey(start, destination);

    // Convert path vector to a comma-separated string
    stringstream ss;
    for (size_t i = 0; i < path.size(); ++i) {
        ss << path[i];
        if (i < path.size() - 1) ss << ",";
    }
    string pathStr = ss.str();

    // ✅ If already exists, update and move to front
    if (cache.find(key) != cache.end()) {
        recentSearches.erase(cache[key].second);
    } 
    // ✅ If cache is full, remove least recently used entry
    else if (recentSearches.size() >= capacity) {
        string lastKey = generateKey(recentSearches.back().first, recentSearches.back().second);
        cache.erase(lastKey);
        recentSearches.pop_back();
    }

    // ✅ Insert new result at the front
    recentSearches.push_front({start, destination});
    cache[key] = {pathStr, recentSearches.begin()};
}

// ✅ Display cache contents (For Debugging)
void LRUCache::displayCache() {
    cout << "📌 LRU Cache Contents:\n";
    for (const auto &search : recentSearches) {
        cout << "🔍 " << search.first << " -> " << search.second << "\n";
    }
}
