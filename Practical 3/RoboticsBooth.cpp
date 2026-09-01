#include "RoboticsBooth.h"

RoboticsBooth::RoboticsBooth(int capacity, std::string name)
    : EventLeaf(name), isOpen(false), active(false), safeMode(true), capacity(capacity), currentVisitors(0), robotsActive(false), requiresPower(true)   
{}

void RoboticsBooth::update(const TechSignal& signal) {
    switch(signal.getType()){
        case TechSignal::Type::FULL_CAPACITY:
            if(currentVisitors >= capacity){
                std::cout << getName() << " is full. No more visitors accepted.\n";
            }
            break;

        case TechSignal::Type::SCHEDULE_CHANGE:
            std::cout << getName() << " received a schedule change: " << signal.getMessage() << std::endl;
            break;

        case TechSignal::Type::POWER_FAILURE:
            active = false;
            robotsActive = false;
            safeMode = true;

            std::cout << getName() << " stopped beacuse of a power failure.\n";
            break;
        
        case TechSignal::Type::EMERGENCY_PAUSE:
            active = false;
            robotsActive = false;
            safeMode = true;

            std::cout << getName() << " stopped its robot showcase for an emergency.\n";
            break;

        case TechSignal::Type::RESUME:
            if(isOpen && safeMode){
                active = true;
                safeMode = false;
                robotsActive = true;

                std::cout << getName() << " resumed its robot showcase.\n";
            }
            break;

        default:
            break;
    }
}

void RoboticsBooth::open(){
    this->isOpen = true;
    this->active = true;
    this->safeMode = false;
    this->robotsActive = true;

    std::cout << getName() << " is now open. Robotics showcase started.\n";
}

void RoboticsBooth::close(){
    this->isOpen = false;
    this->active = false;
    this->safeMode = true;
    this->robotsActive = false;

    std::cout << getName() << " is now closed.\n";
}

std::string RoboticsBooth::getStatus() const{
    std::string output = "";
    std::string temp = getName();
    
    output += temp + " | ";
    
    temp = isOpen ? "OPEN" : "CLOSED";
    output += temp + " | Visitors: ";
    
    temp = std::to_string(currentVisitors);
    output += temp + "/";
    
    temp = std::to_string(capacity);
    output += temp + " | Robots showcase: ";
    
    temp = robotsActive ? "ACTIVE" : "STOPPED";
    output += temp + " | Safe mode: ";

    temp = safeMode ? "ON" : "OFF";
    output += temp + "\n";

    return output;
}

void RoboticsBooth::reportStatus() const{
    std::cout << getStatus();
}

int RoboticsBooth::getCurrentVisitors() const{
    return currentVisitors;
}

int RoboticsBooth::getCapacity() const{
    return this->capacity;
}

int RoboticsBooth::enterVisitor(int visitors){
    if(visitors <= 0)
        return 0;

    if(!isOpen){
        std::cout << getName() << " is closed. Visitors cannot enter.\n";
        return 0;
    }

    int availableSpace = capacity - currentVisitors;
    int accepted = (visitors < availableSpace) ? visitors : availableSpace;

    if(accepted <= 0){
        std::cout << getName() << " is full. No more visitors accepted.\n";

        TechSignal signal(
            TechSignal::Type::FULL_CAPACITY,
            "Robotics Booth has reached full capacity."
        );

        update(signal);

        return 0;
    }

    currentVisitors += accepted;

    std::cout << accepted << " visitor(s) entered "
              << getName() << ". Visitors: "
              << currentVisitors << "/" << capacity << "\n";

    if(currentVisitors >= capacity){
        TechSignal signal(TechSignal::Type::FULL_CAPACITY, "Robotics Booth has reached full capacity."
        );

        update(signal);
    }

    return accepted;
}

int RoboticsBooth::leaveVisitor(int visitors){
    if(visitors <= 0)
        return 0;

    int removed = (visitors < currentVisitors) ? visitors : currentVisitors;

    currentVisitors -= removed;
    std::cout << removed << " visitor(s) left " << getName() << ". Visitors: " << currentVisitors << "/" << capacity << "\n";
    return removed;
}


