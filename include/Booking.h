#ifndef BOOKING_H
#define BOOKING_H

#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// Structure for Seat
struct Seat {
    int price;
    int seatNumber;
    string classType;

    // Custom comparator for Min Heap (Priority Queue)
    bool operator>(const Seat& other) const {
        if (price == other.price)
            return classType > other.classType;  // Business class has higher priority
        return price > other.price;
    }
};

class BookingSystem {
private:
    priority_queue<Seat, vector<Seat>, greater<Seat>> minHeap;  // Min Heap for seat allocation
    unordered_map<int, int> basePrices;  // Stores original prices
    int bookedSeats, totalSeats;
    bool priceIncreased; // Flag to ensure price is increased only once

    void adjustPrices();  // Function to handle price hikes based on demand

public:
    BookingSystem();  // Constructor
    void addSeat(int seatNumber, int price, string classType);
    void bookSeat();
    void displayAvailableSeats();
};

#endif // BOOKING_H
