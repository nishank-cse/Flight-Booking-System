#include "Booking.h"

// Constructor
BookingSystem::BookingSystem() : bookedSeats(0), totalSeats(0), priceIncreased(false) {}

// Function to adjust prices dynamically based on demand
void BookingSystem::adjustPrices() {
    if (priceIncreased) return;  // Ensure price is increased only once

    double demandFactor = (double)bookedSeats / totalSeats;
    if (demandFactor > 0.5) {  // Trigger price hike when >50% seats are booked
        priority_queue<Seat, vector<Seat>, greater<Seat>> tempHeap;

        while (!minHeap.empty()) {
            Seat s = minHeap.top();
            minHeap.pop();

            // Increase price by 10% of the original base price
            s.price = basePrices[s.seatNumber] + (basePrices[s.seatNumber] * 0.1);
            tempHeap.push(s);
        }

        minHeap = tempHeap;
        priceIncreased = true;  // Prevent further hikes
        cout << "⚠️ Prices increased by 10% due to high demand!\n";
    }
}

void BookingSystem::addSeat(int seatNumber, int price, string classType) {
    minHeap.push({price, seatNumber, classType});
    basePrices[seatNumber] = price; // Store base price
    totalSeats++;
}

void BookingSystem::bookSeat() {
    if (minHeap.empty()) {
        cout << "No seats available!\n";
        return;
    }

    Seat bookedSeat = minHeap.top();
    minHeap.pop();
    bookedSeats++;

    cout << "✅ Seat " << bookedSeat.seatNumber << " booked (" 
         << bookedSeat.classType << ", Price: " << bookedSeat.price << ")\n";

    // Adjust prices after booking
    adjustPrices();
}

void BookingSystem::displayAvailableSeats() {
    priority_queue<Seat, vector<Seat>, greater<Seat>> tempHeap = minHeap;  // Copy of heap

    cout << "\n📌 Available Seats:\n";
    while (!tempHeap.empty()) {
        Seat s = tempHeap.top();
        cout << "Seat " << s.seatNumber << " (" << s.classType 
             << ", Price: " << s.price << ")\n";
        tempHeap.pop();
    }
}
