# C++ Projects Overview

This repository contains several C++ programs demonstrating various concepts and functionalities.

## Parts Overview

### Parts 1, 2, and 3: Sensor Data Analysis
These three parts are implemented in the same C++ file, focusing on sensor data analysis:

- **Part 1**: Count the number of sensor data registrations for "Altitude" on the date 2012-01-02.
- **Part 2**: Check for any "SpeedInKmh" registrations with a speed over 99.9. If found, print "Maxhastighet uppnådd"; otherwise, print "Ingen maxhastighet uppnådd."
- **Part 3**: Update all "FuelConsumption" sensor records by increasing the value by 75%.

### Part 4: Healthcare Center Simulator
This program simulates a healthcare center using a queue system:
- Customers can be added to the waiting queue, each represented by a class containing a queue number, name, and arrival time.
- The program can also call in the next customer and display how long they have waited.

### Part 5: ATM System with Maps
This program implements a simple ATM system using a map:
- The key is the account number, and the value is the account balance.
- Users can create accounts, log in, deposit, and withdraw money through a menu interface.

### Part 6: Hockey Player LRU Cache
This program manages hockey players using an LRU (Least Recently Used) cache:
- It creates a file with 100,000 random hockey players, each represented by an ID, name, jersey number, and team name.
- The `LRUCache` class allows retrieving players by ID, using a cache for efficiency.

---

### Skills Demonstrated
- C++ programming fundamentals (I/O, arrays, and control structures).
- File handling and data manipulation.
- Object-oriented programming (OOP) and class management.
- Implementation of caching mechanisms (LRU cache).
- Data structures (queues and maps).
