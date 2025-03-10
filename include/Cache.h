#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <list>
#include <string>
#include <vector>

using namespace std;

class LRUCache {
private:
    int capacity; // Maximum cache size (3-5 searches)
    list<pair<string, string>> recentSearches; // Doubly Linked List (LRU Order)
    unordered_map<string, pair<string, list<pair<string, string>>::iterator>> cache; // Hash Map for O(1) access

    // Generate a unique key for each search
    string generateKey(const string &start, const string &destination);

public:
    LRUCache(int size); // Constructor

    // Get search result from cache (if exists), else return empty vector
    vector<string> getSearchResult(const string &start, const string &destination);

    // Store new search result in cache
    void putSearchResult(const string &start, const string &destination, const vector<string> &path);

    // Display cache contents (For Debugging)
    void displayCache();
};

#endif // CACHE_H
