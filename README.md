# Projecty
# Projecty - Smart Parking Slot Tracker

A terminal-based parking lot management system built in C++23. The idea was to implement common data structures like circular queues and fixed-size arrays in a practical context rather than just textbook examples.

## What it does

The program runs an interactive console where an operator can manage a small parking lot (10 slots). You get a menu with options to:

- Park a vehicle in the next available slot
- Release a specific slot when a vehicle leaves
- View all slots and their current status (occupied or available)
- View a log of recent departures

The departure history uses a circular queue with a capacity of 5, so it only keeps the most recent records and older ones get overwritten automatically. Slot assignment is first-come-first-served — it scans from slot 1 to 10 and parks in the first empty one.

## Project structure

```
projecty/
  src/
    main.cpp                  -- entry point, handles the menu loop
    includes/
      parking.hpp             -- parking lot structs and core logic (park, release, occupancy)
      queue.hpp               -- generic circular queue template class
      departure_queue.cpp     -- display logic for departure records
      utils.hpp               -- terminal helpers, input validation, formatting
  xmake.lua                   -- build configuration
  Dockerfile                  -- containerized build setup
```

## Data structures used

- **Fixed-size array** for the parking slots (10 slots, stored as an array of structs)
- **Circular queue** (template class) for departure history — overwrites the oldest entry when full
- **Structs** for parking slots and departure records

## How to build and run

### Local (requires xmake + C++23 compiler)

```bash
xmake
xmake run projecty
```

GCC 14+, Clang 17+, or MSVC 19.35+ should work. The project uses `std::format` which needs C++23 support.

### Docker (no local setup needed)

```bash
docker build -t projecty .
docker run --rm -it projecty
```

## Contributing

Fork the repo, make a branch, push your changes, and open a PR. Make sure `xmake` builds without errors before submitting. Don't commit build artifacts.

A small C++23 project built with Xmake and Docker.

## Requirements

- Git
- Docker Desktop on Windows/macOS, or Docker Engine on Linux

No local C++ compiler or Xmake installation is required.

## Getting started

Clone the repository:

```bash
git clone https://github.com/almeidaorville7-lang/projecty.git
cd projecty
```

Build the project:

```bash
docker build -t projecty .
```

Run the project:

```bash
docker run --rm -it projecty
```

Rebuild the Docker image after modifying the source code.

## Local development--

For contributors who already have Xmake and a compatible C++23 compiler:

```bash
xmake
xmake run projecty
```

## Contributing

1. Create a feature branch.
2. Make your changes.
3. Verify the Docker build succeeds.
4. Open a pull request against `main`.

Do not commit generated build files or compiled executables.
