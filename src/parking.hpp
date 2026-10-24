#pragma once

#include <string>

/**
 * @file parking.hpp
 * @brief Defines the data structures and constants for the Smart Parking Slot Tracker.
 *
 * This header defines the parking capacity, departure history capacity,
 * parking slots, departure records, the circular departure queue, and
 * the parking lot structure.
 *
 * It also declares the functions used to manage the departure queue,
 * allowing the parking system to access and update departure history.
 */

const int PARKING_CAPACITY = 10; // Total number of slots
const int HISTORY_CAPACITY = 5; // Number of records in departure history

// Individual slot in the parking lot
struct parking_slot {
    int slot_id;
    bool is_occupied;
    std::string vehicle_id;
};

// Individual record in the departure history
struct departure_record {
    std::string vehicle_id;
    int slot_id;
};

// Queue of departure history 
struct departure_queue {
    departure_record records[HISTORY_CAPACITY];
    int front; // Index of the oldest departure
    int rear;  // Index of the newest departure
    int count; // Number of records currently stored

    departure_queue() {
        front = 0;
        rear = -1;
        count = 0;
    }
};

// ParkingLot which contains the parking slots and the departure queue
struct parking_lot {
    parking_slot slots[PARKING_CAPACITY];
    departure_queue departure_history;
};

// Departure queue operations
bool is_queue_empty(const departure_queue& queue);
bool is_queue_full(const departure_queue& queue);

void enqueue(
    departure_queue& queue,
    const departure_record& record_to_enqueue
);

void display_queue(const departure_queue& queue);
