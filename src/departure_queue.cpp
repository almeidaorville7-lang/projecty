#include <iostream>
#include <iomanip>
#include "parking.hpp"

/**
 * @file departure_queue.cpp
 * @brief Implements the circular queue used to track recent vehicle departures.
 *
 * This file implements operations to check whether the departure queue
 * is empty or full, enqueue new departure records, and display the
 * stored departure history.
 *
 * The queue has a fixed capacity and retains only the five most recent
 * departures. When the queue is full, adding a new record overwrites
 * the oldest departure, maintaining the history in chronological order.
 */
 
/** Use count to determine if queue is empty */
bool is_queue_empty(const departure_queue& queue) {
    return queue.count == 0;
}

/** Use count to determine if queue is full */
bool is_queue_full(const departure_queue& queue) {
    return queue.count == HISTORY_CAPACITY;
}

/** Enqueue into the departure queue */
void enqueue(
    departure_queue& queue,
    const departure_record& record_to_enqueue
) {

    // If queue is full, increment front
    if (is_queue_full(queue)) {
        queue.front = (queue.front + 1) % HISTORY_CAPACITY;
    }

    // If queue is not full, increment count
    else {
        queue.count++;
    }

    // Increment rear and place the record at rear
    queue.rear = (queue.rear + 1) % HISTORY_CAPACITY;
    queue.records[queue.rear] = record_to_enqueue;
}

/** Displays all the records in the queue */
void display_queue(const departure_queue& queue) {

    // If queue is empty, return early.
    if (is_queue_empty(queue)) {
        std::cout << "No recent departures have taken place.";
        return;
    }

    // Header for displaying records
    std::cout << " ————— Recent Departures ————— \n";
    std::cout << "|  Vehicle ID  |    Slot ID   |\n";
    std::cout << " ————————————————————————————— \n";

    // Iterate through the records currently stored in the queue
    for (int record_offset = 0; 
        record_offset < queue.count;
        record_offset++
    ) {
        // Store index, incase of wrapping around
        int record_index = (record_offset + queue.front) % HISTORY_CAPACITY;

        // Store the record at the record index
        const departure_record& record = queue.records[record_index];

        // Print the details of the current record
        std::cout << std::left
            << "| " << std::setw(15) << record.vehicle_id
            << "| " << std::setw(12) << record.slot_id
            << "|\n";
        
        // Loop continues until count. 
    }
}
