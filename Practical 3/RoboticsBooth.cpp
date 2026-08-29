#include "RoboticsBooth.h"

RoboticsBooth::RoboticsBooth(int capacity, std::string name)
    : EventComponent(name), isOpen(false), active(false), safeMode(true), capacity(capacity), currentVisitors(0), robotsActive(false), requiresPower(true)   
{}

void RoboticsBooth::update(const TechSignal& signal) {
    switch(signal.getType()){
        case TechSignal::Type::FULL_CAPACITY:
            if(currentVisitors >= capacity){
                std::cout << getName() << " is full. No more visitors accepted.\n";
            }
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

void RoboticsBooth::reportStatus() const{
    std::cout << getName() << " | " << (isOpen ? "OPEN" : "CLOSED") << " | Visitors: " << currentVisitors << "/" << capacity << " | Robots showcase: " << (robotsActive ? "ACTIVE" : "STOPPED") << std::endl;
}

int RoboticsBooth::getCapacity() const{
    return this->capacity;
}