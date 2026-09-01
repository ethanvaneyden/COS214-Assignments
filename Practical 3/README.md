# EventFlow

## Event Concept

EventFlow models a dynamic technology expo. The system represents different zones and areas within the expo and supports commands that are propagated down the event hierarchy.

## Team Members

* Ethan Van Eyden
* Lesego Tebeile
* Mogale Kagiso Lebethe

## Build Instructions

1. Type `make` to compile the program.
2. Type `make valgrind` to run the program with memory leak checking.
3. Type `make clean` to remove compiled files and coverage data.
4. Type `make coverage` to generate an HTML code coverage report.

## Architecture Overview

The system uses the **Composite** and **Observer** design patterns. The Composite pattern represents the expo as a hierarchy of zones, areas, and individual event units. For example, a zone such as the Main Stage can contain smaller event areas and units.

Composite nodes can also act as both **Observers and Subjects**. This allows them to receive signals from their parent and propagate relevant notifications further down the hierarchy to their children. Leaf nodes however can only ever act as **Oberservers** as they have no children.

Memory management is centralised in the `ExpoRegistry` class, which manages the lifecycle of the objects in the system and simplifies memory management throughout the application.
