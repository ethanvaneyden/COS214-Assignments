#include <iostream>
#include <string>
#include <sstream>
#include "ExpoRegistry.h"
#include "MapBuilder.h"
#include "TechSignal.h"

void printHelp() {
    std::cout << "\n================ EXPO COMMAND MENU ================\n"
              << "  map                       : Print the EXPO map\n"
              << "  status                    : Print operational status report\n"
              << "  capacity <name>           : Show capacity info for a component\n"
              << "  enter <name> <count>      : Admit visitors into a component\n"
              << "  leave <name> <count>      : Remove visitors from a component\n"
              << "  signal <target> <type>    : Send TechSignal (OPEN, CLOSE, POWER_FAILURE, etc.)\n"
              << "  move <child> <new_parent> : Relocate a component using operator>>\n"
              << "  help                      : Show this menu\n"
              << "  exit                      : Quit application\n"
              << "===================================================\n\n";
}

int main() {
    ExpoRegistry registry;

    MapBuilder mapBuilder;
    mapBuilder.build(registry);

    if (auto* hall = registry.findComponent("Main Exhibition Hall")) {
        hall->open();
    }

    std::cout << "====================================================\n"
              << "      WELCOME TO THE EXPO MANAGEMENT SYSTEM         \n"
              << "====================================================\n";
    printHelp();

    std::string line;
    while (true) {
        std::cout << "expo> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit" || command == "quit") {
            std::cout << "Exiting Expo System. Goodbye!\n";
            break;
        } 
        else if (command == "map") {
            registry.printMap();
        } 
        else if (command == "status") {
            registry.printStatusReport();
        } 
        else if (command == "help") {
            printHelp();
        } 
        else if (command == "capacity") {
            std::string name;
            if (ss >> name) {
                registry.printCapacity(name);
            } else {
                std::cout << "Usage: capacity <component_name>\n";
            }
        } 
        else if (command == "enter") {
            std::string name;
            int count = 0;
            if (ss >> name >> count) {
                int admitted = registry.enterVisitors(name, count);
                std::cout << "[Registry] Admitted " << admitted << " visitors to '" << name << "'.\n";
            } else {
                std::cout << "Usage: enter <component_name> <count>\n";
            }
        } 
        else if (command == "leave") {
            std::string name;
            int count = 0;
            if (ss >> name >> count) {
                int removed = registry.leaveVisitors(name, count);
                std::cout << "[Registry] Removed " << removed << " visitors from '" << name << "'.\n";
            } else {
                std::cout << "Usage: leave <component_name> <count>\n";
            }
        } 
        else if (command == "move") {
            std::string childName, parentName;
            if (ss >> childName >> parentName) {
                if (registry.moveComponent(childName, parentName)) {
                    std::cout << "[Registry] Moved '" << childName << "' to '" << parentName << "' via operator>>.\n";
                }
            } else {
                std::cout << "Usage: move <child_name> <new_parent_name>\n";
            }
        } 
        else if (command == "signal") {
            std::string targetName, signalTypeStr;
            if (ss >> targetName >> signalTypeStr) {
                TechSignal signal(signalTypeStr, "Broadcasting user-issued CLI signal.");
                if (registry.transmitSignal(targetName, signal)) {
                    std::cout << "[Registry] TechSignal dispatched to '" << targetName << "'.\n";
                }
            } else {
                std::cout << "Usage: signal <target_name> <open|close|power failure|emergency pause|full capacity>\n";
            }
        } 
        else {
            std::cout << "Unknown command. Type 'help' for available options.\n";
        }
    }

    return 0;
}