#include <iostream>
#include <string>
#include <sstream>

#include "ExpoRegistry.h"
#include "MapBuilder.h"
#include "TechSignal.h"

void printHelp() {
    std::cout
        << "\n================ EXPO COMMAND MENU ================\n"
        << "  map                              : Print the EXPO map\n"
        << "  status                           : Print operational status report\n"
        << "  capacity <name>                  : Show capacity info for a component\n"
        << "  enter <name> <count>             : Admit visitors into a component\n"
        << "  leave <name> <count>             : Remove visitors from a component\n"
        << "  signal <target> <type>           : Send a TechSignal\n"
        << "  move <child> <new_parent>        : Relocate a component using operator>>\n"
        << "  help                             : Show this menu\n"
        << "  exit                             : Quit application\n"
        << "\n"
        << "Signal types:\n"
        << "  open\n"
        << "  close\n"
        << "  resume\n"
        << "  full_capacity\n"
        << "  change_schedule\n"
        << "  power_failure\n"
        << "  emergency_pause\n"
        << "  network_failure\n"
        << "===================================================\n\n";
}

int main() {
    ExpoRegistry registry;

    // ---------------------------------------------------------------------
    // STEP 1: Build the exhibition hierarchy.
    //
    // MapBuilder creates the components and registers them in ExpoRegistry.
    // ---------------------------------------------------------------------
    MapBuilder mapBuilder;
    mapBuilder.build(registry);

    // ---------------------------------------------------------------------
    // FIXED ERROR:
    //
    // The ExhibitionHall constructor names the root:
    //
    //     "Main_Exhibition_Hall"
    //
    // Previously main() searched for:
    //
    //     "Main Exhibition Hall"
    //
    // ExpoRegistry uses the component name as the lookup-table key, so
    // spaces and underscores do NOT represent the same name.
    //
    // Because of the old mismatch, findComponent() returned nullptr and
    // the hall was never opened during application startup.
    //
    // We now use the exact same canonical name that MapBuilder registers.
    // ---------------------------------------------------------------------
    if (auto* hall = registry.findComponent("Main_Exhibition_Hall")) {
        hall->open();
    } else {
        // This should never happen if MapBuilder successfully constructs
        // the root component. The message makes a configuration/building
        // problem much easier to diagnose.
        std::cerr
            << "[Main Error] Main_Exhibition_Hall could not be found "
               "in the registry.\n";
    }

    // ---------------------------------------------------------------------
    // Display the application welcome message and available commands.
    // ---------------------------------------------------------------------
    std::cout
        << "====================================================\n"
        << "      WELCOME TO THE EXPO MANAGEMENT SYSTEM         \n"
        << "====================================================\n";

    printHelp();

    // ---------------------------------------------------------------------
    // Command-line processing loop.
    // ---------------------------------------------------------------------
    std::string line;

    while (true) {
        std::cout << "EventFlow> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        // Stop the application if input is closed or unavailable.
        if (!std::getline(std::cin, line)) {
            break;
        }

        // Ignore empty commands.
        if (line.empty()) {
            continue;
        }

        // Use a string stream to separate the command from its arguments.
        std::stringstream ss(line);

        std::string command;
        ss >> command;

        // -----------------------------------------------------------------
        // EXIT
        // -----------------------------------------------------------------
        if (command == "exit" || command == "quit") {
            std::cout
                << "Exiting Expo System. Goodbye!\n";
            break;
        }

        // -----------------------------------------------------------------
        // MAP
        // -----------------------------------------------------------------
        else if (command == "map") {
            registry.printMap();
        }

        // -----------------------------------------------------------------
        // STATUS
        // -----------------------------------------------------------------
        else if (command == "status") {
            registry.printStatusReport();
        }

        // -----------------------------------------------------------------
        // HELP
        // -----------------------------------------------------------------
        else if (command == "help") {
            printHelp();
        }

        // -----------------------------------------------------------------
        // CAPACITY
        //
        // Example:
        //     capacity Main_Stage
        // -----------------------------------------------------------------
        else if (command == "capacity") {
            std::string name;

            if (ss >> name) {
                registry.printCapacity(name);
            } else {
                std::cout
                    << "Usage: capacity <component_name>\n";
            }
        }

        // -----------------------------------------------------------------
        // ENTER
        //
        // Example:
        //     enter Robotics_Booth 10
        //
        // The actual visitor handling is delegated to the component through
        // ExpoRegistry, preserving the Composite interface.
        // -----------------------------------------------------------------
        else if (command == "enter") {
            std::string name;
            int count = 0;

            if (ss >> name >> count) {
                int admitted =
                    registry.enterVisitors(name, count);

                std::cout
                    << "[Registry] Admitted "
                    << admitted
                    << " visitors to '"
                    << name
                    << "'.\n";
            } else {
                std::cout
                    << "Usage: enter <component_name> <count>\n";
            }
        }

        // -----------------------------------------------------------------
        // LEAVE
        //
        // Example:
        //     leave Robotics_Booth 5
        // -----------------------------------------------------------------
        else if (command == "leave") {
            std::string name;
            int count = 0;

            if (ss >> name >> count) {
                int removed =
                    registry.leaveVisitors(name, count);

                std::cout
                    << "[Registry] Removed "
                    << removed
                    << " visitors from '"
                    << name
                    << "'.\n";
            } else {
                std::cout
                    << "Usage: leave <component_name> <count>\n";
            }
        }

        // -----------------------------------------------------------------
        // MOVE
        //
        // Example:
        //     move Demo_Area Main_Stage
        //
        // ExpoRegistry eventually invokes:
        //
        //     (*child) >> (*newParent);
        //
        // which uses the overloaded operator>> to relocate the component.
        // -----------------------------------------------------------------
        else if (command == "move") {
            std::string childName;
            std::string parentName;

            if (ss >> childName >> parentName) {
                if (registry.moveComponent(
                        childName,
                        parentName)) {

                    std::cout
                        << "[Registry] Moved '"
                        << childName
                        << "' to '"
                        << parentName
                        << "' via operator>>.\n";
                }
            } else {
                std::cout
                    << "Usage: move <child_name> <new_parent_name>\n";
            }
        }

        // -----------------------------------------------------------------
        // SIGNAL
        //
        // Example:
        //     signal Main_Stage open
        //
        // IMPORTANT:
        // TechSignal::parseType() is case-sensitive and expects strings
        // such as "open" and "power_failure".
        //
        // The command therefore needs to use the same vocabulary as
        // TechSignal.
        // -----------------------------------------------------------------
        else if (command == "signal") {
            std::string targetName;
            std::string signalTypeStr;

            if (ss >> targetName >> signalTypeStr) {

                TechSignal signal(
                    signalTypeStr,
                    "Broadcasting user-issued CLI signal."
                );

                if (registry.transmitSignal(
                        targetName,
                        signal)) {

                    std::cout
                        << "[Registry] TechSignal dispatched to '"
                        << targetName
                        << "'.\n";
                }
            } else {
                std::cout
                    << "Usage: signal <target_name> <signal_type>\n"
                    << "Signal types: open, close, resume, "
                       "full_capacity, change_schedule, "
                       "power_failure, emergency_pause, "
                       "network_failure\n";
            }
        }

        // -----------------------------------------------------------------
        // UNKNOWN COMMAND
        // -----------------------------------------------------------------
        else {
            std::cout
                << "Unknown command. "
                   "Type 'help' for available options.\n";
        }
    }

    return 0;
}
