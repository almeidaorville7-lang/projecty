/**
 * @file departure_queue.cpp
 * @brief Implements departure-specific operations for the Smart Parking Slot Tracker.
 *
 * This file implements functions specific to displaying and managing
 * vehicle departure records.
 */

#pragma once

#include "parking.hpp"
#include "utils.hpp"

/**
 * @brief Displays all recent vehicle departures stored in the departure queue.
 * @param queue The departure queue to display.
 */
inline void display_queue(const departure_queue &queue)
{
    // If queue is empty, return early.
    if (queue.is_empty())
    {
        println("No recent departures have taken place.");
        return;
    }

    // Header for displaying records
    println(" ————— Recent Departures ————— ");
    println("|  Vehicle ID  |    Slot ID   |");
    println(" ————————————————————————————— ");

    // Iterate through the records currently stored in the queue
    for (int record_offset = 0; record_offset < queue.count; record_offset++)
    {
        // Store index, in case of wrapping around
        int record_index = (record_offset + queue.front) % HISTORY_CAPACITY;

        // Store the record at the record index
        const departure_record &record = queue.records[record_index];

        // Print the details of the current record using format and println
        println(format("| {:<14} | {:<12} |", record.vehicle_id, record.slot_id));
    }
}
