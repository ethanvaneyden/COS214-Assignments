#include "AIDemoBooth.h"

AIDemoBooth::AIDemoBooth(EventComponent *parent)
    : EventLeaf("AI_Demo_Booth", parent), isOpen(false), active(false), capacity(20),
      currentVisitors(0), requiresNetwork(true), demoRunning(false) {
    lastMessage = "Normal operation";
}

void AIDemoBooth::update(const TechSignal &signal) {
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
    case TechSignal::Type::NETWORK_FAILURE:
        if (requiresNetwork) {
            demoRunning = false;
            lastMessage = "Paused due to network failure";
        }
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
        demoRunning = false;
        lastMessage = "Power failure";
        break;
    case TechSignal::Type::EMERGENCY_PAUSE:
        active = false;
        demoRunning = false;
        lastMessage = "Emergency pause";
        break;
    case TechSignal::Type::RESUME:
        if (isOpen) {
            active = true;
            demoRunning = true;
            lastMessage = "Resumed operation";
        }
        break;
    default:
        break;
    }
}

void AIDemoBooth::open() {
    isOpen = true;
    active = true;
    demoRunning = true;
    lastMessage = "Now open";
}

void AIDemoBooth::close() {
    isOpen = false;
    active = false;
    demoRunning = false;
    lastMessage = "Now closed";
}

int AIDemoBooth::getCapacity() const {
    return capacity;
}

int AIDemoBooth::getCurrentVisitors() const {
    return currentVisitors;
}

int AIDemoBooth::enterVisitor(int visitors) {
    if (visitors <= 0 || !isOpen) return 0;

    int availableSpace = capacity - currentVisitors;
    int accepted = (visitors < availableSpace) ? visitors : availableSpace;
    currentVisitors += accepted;
    return accepted;
}

int AIDemoBooth::leaveVisitor(int visitors) {
    if (visitors <= 0) return 0;

    int removed = (visitors < currentVisitors) ? visitors : currentVisitors;
    currentVisitors -= removed;
    return removed;
}

std::string AIDemoBooth::getStatus() const {
    std::string stateStr = getName() + " | ";
    stateStr += (isOpen ? "OPEN" : "CLOSED") + std::string(" | Visitors: ");
    stateStr += std::to_string(currentVisitors) + "/" + std::to_string(capacity);
    stateStr += " | Demo: " + std::string(demoRunning ? "RUNNING" : "STOPPED");
    stateStr += " | Active: " + std::string(active ? "YES" : "NO");
    stateStr += " | Status: " + lastMessage;
    return "- " + stateStr + "\n";
}