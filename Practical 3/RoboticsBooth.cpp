#include "RoboticsBooth.h"

RoboticsBooth::RoboticsBooth(EventComponent *parent)
    : EventLeaf("Robotics_Booth", parent), isOpen(false), active(false), safeMode(true),
      capacity(25), currentVisitors(0), robotsActive(false), lastMessage("Normal operation") {}

void RoboticsBooth::update(const TechSignal &signal) {
    switch (signal.getType()) {
    case TechSignal::Type::UNKNOWN:
        lastMessage = "Unknown signal received";
        break;
    case TechSignal::Type::OPEN:
        open();
        break;
    case TechSignal::Type::CLOSE:
        close();
        break;
    case TechSignal::Type::FULL_CAPACITY:
        lastMessage = "Reached full capacity";
        break;
    case TechSignal::Type::SCHEDULE_CHANGE:
        lastMessage = "Schedule change: " + signal.getMessage();
        break;
    case TechSignal::Type::POWER_FAILURE:
        isOpen = false;
        active = false;
        robotsActive = false;
        safeMode = true;
        lastMessage = "Power failure";
        break;
    case TechSignal::Type::EMERGENCY_PAUSE:
        active = false;
        robotsActive = false;
        safeMode = true;
        lastMessage = "Emergency pause";
        break;
    case TechSignal::Type::RESUME:
        if (isOpen) {
            active = true;
            safeMode = false;
            robotsActive = true;
            lastMessage = "Resumed operation";
        }
        break;
    default:
        break;
    }
}

void RoboticsBooth::open() {
    isOpen = true;
    active = true;
    safeMode = false;
    robotsActive = true;
    lastMessage = "Now open";
}

void RoboticsBooth::close() {
    isOpen = false;
    active = false;
    safeMode = true;
    robotsActive = false;
    lastMessage = "Now closed";
}

int RoboticsBooth::getCapacity() const {
    return capacity;
}

int RoboticsBooth::getCurrentVisitors() const {
    return currentVisitors;
}

int RoboticsBooth::enterVisitor(int visitors) {
    if (visitors <= 0 || !isOpen) return 0;

    int availableSpace = capacity - currentVisitors;
    int accepted = (visitors < availableSpace) ? visitors : availableSpace;
    currentVisitors += accepted;
    return accepted;
}

int RoboticsBooth::leaveVisitor(int visitors) {
    if (visitors <= 0) return 0;

    int removed = (visitors < currentVisitors) ? visitors : currentVisitors;
    currentVisitors -= removed;
    return removed;
}

std::string RoboticsBooth::getStatus() const {
    std::string stateStr = getName() + " | ";
    stateStr += (isOpen ? "OPEN" : "CLOSED") + std::string(" | Visitors: ");
    stateStr += std::to_string(currentVisitors) + "/" + std::to_string(capacity);
    stateStr += " | Robots: " + std::string(robotsActive ? "ACTIVE" : "STOPPED");
    stateStr += " | SafeMode: " + std::string(safeMode ? "ON" : "OFF");
    stateStr += " | Status: " + lastMessage;
    return "- " + stateStr + "\n";
}