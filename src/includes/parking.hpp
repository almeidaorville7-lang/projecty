/**
 * @file parking.hpp
 * @brief Data structures and operations for the parking tracker.
 */

#pragma once

#include "queue.hpp"
#include "utils.hpp"
#include <string>

// Capacities
/**
 * @brief Total number of parking slots available in the facility.
 */
const int PARKING_CAPACITY = 10;

/**
 * @brief Maximum number of recent vehicle departure records retained in the history queue.
 */
const int HISTORY_CAPACITY = 5;

/**
 * @brief Represents an individual parking slot in the facility.
 */
struct parking_slot
{
    int slot_id;            ///< Unique identifier for the slot (1-based: 1 to PARKING_CAPACITY).
    bool is_occupied;       ///< True if currently occupied by a vehicle, false if vacant.
    std::string vehicle_id; ///< Vehicle registration ID if occupied, empty string otherwise.
};

/**
 * @brief Represents a logged record of a departed vehicle.
 */
struct departure_record
{
    std::string vehicle_id; ///< Registration identifier of the departed vehicle.
    int slot_id;            ///< The slot number that was released.
};

/**
 * @brief Type alias for the circular departure history queue.
 */
using departure_queue = Queue<departure_record, HISTORY_CAPACITY>;

/**
 * @brief Composite data structure representing the entire parking facility.
 *
 * Holds the fixed array of parking slots and the circular queue of recent departures.
 */
struct parking_lot
{
    parking_slot slots[PARKING_CAPACITY]; ///< Fixed array of all parking slots.
    departure_queue departure_history;    ///< Circular queue storing recent departure history.
};

/**
 * @brief Initializes all slots in the parking lot as available.
 * @param lot The parking lot to set up.
 */
inline void init_parking_lot(parking_lot &lot)
{
    for (int i = 0; i < PARKING_CAPACITY; i++)
    {
        lot.slots[i].slot_id = i + 1;
        lot.slots[i].is_occupied = false;
        lot.slots[i].vehicle_id = "";
    }
}

/**
 * @brief Parks a vehicle in the first free slot.
 * @param lot The parking lot.
 * @param vehicle_id The vehicle identifier.
 * @return Assigned slot ID (1-10), or -1 if full.
 */
inline int park_vehicle(parking_lot &lot, const std::string &vehicle_id)
{
    for (int i = 0; i < PARKING_CAPACITY; i++)
    {
        if (!lot.slots[i].is_occupied)
        {
            lot.slots[i].is_occupied = true;
            lot.slots[i].vehicle_id = vehicle_id;
            println(format("Vehicle '{}' parked in Slot {}.", vehicle_id, lot.slots[i].slot_id));
            return lot.slots[i].slot_id;
        }
    }

    println(format("Parking full! Cannot park '{}'.", vehicle_id));
    return -1;
}

/**
 * @brief Releases a slot and records departure in history.
 * @param lot The parking lot.
 * @param slot_id The slot ID to release (1-10).
 * @return True if released, false if invalid or already empty.
 */
inline bool release_slot(parking_lot &lot, int slot_id)
{
    if (slot_id < 1 || slot_id > PARKING_CAPACITY)
    {
        println(format("Invalid Slot {}. Must be between 1 and {}.", slot_id, PARKING_CAPACITY));
        return false;
    }

    parking_slot &slot = lot.slots[slot_id - 1];
    if (!slot.is_occupied)
    {
        println(format("Slot {} is already empty.", slot_id));
        return false;
    }

    // Save departure to history queue
    departure_record record = {slot.vehicle_id, slot.slot_id};
    lot.departure_history.enqueue(record);

    println(format("Slot {} released. Vehicle '{}' departed.", slot_id, slot.vehicle_id));

    // Reset slot
    slot.is_occupied = false;
    slot.vehicle_id = "";
    return true;
}

/**
 * @brief Displays the current status of all parking slots.
 * @param lot The parking lot.
 */
inline void show_occupancy(const parking_lot &lot)
{
    printHeader("Parking Lot Occupancy", 45);
    int occupied = 0;

    println(format("| {:<8} | {:<10} | {:<16} |", "Slot ID", "Status", "Vehicle ID"));
    println(std::string(45, '-'));

    for (int i = 0; i < PARKING_CAPACITY; i++)
    {
        const parking_slot &slot = lot.slots[i];
        if (slot.is_occupied)
        {
            occupied++;
            println(format("| Slot {:<3} | Occupied   | {:<16} |", slot.slot_id, slot.vehicle_id));
        }
        else
        {
            println(format("| Slot {:<3} | Available  | {:<16} |", slot.slot_id, "---"));
        }
    }

    println(std::string(45, '='));
    println(format("Occupied: {} | Available: {} | Total: {}",
                   occupied, PARKING_CAPACITY - occupied, PARKING_CAPACITY));
    println("");
}
