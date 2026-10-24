/**
 * @file main.cpp
 * @brief Interactive Operator Console for the Smart Parking Slot Tracker.
 */

#include "includes/departure_queue.cpp"
#include "includes/parking.hpp"
#include "includes/utils.hpp"

int main()
{
    // Clear terminal on startup
    clearScreen();

    // Create the parking lot structure
    parking_lot lot;

    // Set up and initialize all slots as available (1 to PARKING_CAPACITY)
    init_parking_lot(lot);

    println("");
    printHeader("SMART PARKING SLOT TRACKER", 50);
    println("Operator management console initialized.");
    println("");

    bool running = true;

    // Main interactive loop
    do
    {
        // Display operator menu
        printHeader("MAIN MENU", 50);
        println("1. Park Vehicle (First Free Slot)");
        println("2. Release Slot");
        println("3. Show Occupancy");
        println("4. Show Recent Departures");
        println("5. Exit");
        println(std::string(50, '-'));

        // Read operator selection using readInt from utils.hpp
        int choice = readInt("Select an option (1-5): ");
        if (choice == -1)
        {
            // Input stream closed or at EOF
            break;
        }
        println("");

        // Process operator selection via switch-case
        switch (choice)
        {
        case 1:
        {
            printHeader("PARK VEHICLE", 45);
            std::string vehicle_id = readString("Enter Vehicle ID to park: ");
            if (!vehicle_id.empty())
            {
                park_vehicle(lot, vehicle_id);
            }
            else if (!std::cin)
            {
                running = false;
            }
            println("");
            break;
        }

        case 2:
        {
            printHeader("RELEASE SLOT", 45);
            int slot_id = readInt(format("Enter Slot ID to release (1-{}): ", PARKING_CAPACITY));
            if (slot_id != -1)
            {
                release_slot(lot, slot_id);
            }
            println("");
            break;
        }

        case 3:
        {
            show_occupancy(lot);
            break;
        }

        case 4:
        {
            printHeader("RECENT DEPARTURES", 45);
            display_queue(lot.departure_history);
            println("");
            break;
        }

        case 5:
        {
            println("Exiting Smart Parking Tracker. Goodbye!");
            running = false;
            break;
        }

        default:
        {
            println(format("Invalid choice '{}'. Please enter a number from 1 to 5.\n", choice));
            break;
        }
        }
    } while (running);

    return 0;
}
