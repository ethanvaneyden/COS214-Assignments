#include "AIDemoBooth.h"

AIDemoBooth::AIDemoBooth(int capacity, std::string name)
    : EventComponent(name), isOpen(false), active(false), capacity(capacity), currentVisitors(0), requiresNetwork(true), demoRunning(false)   
{}

void AIDemoBooth::update(const TechSignal& signal) {
    switch(signal.getType()){
        case TechSignal::Type::NETWORK_FAILURE:
            if(this->requiresNetwork){
                this->demoRunning = false;
                std::cout << getName() << " paused its AI Demonstration due to network failure.\n";
            }
            break;

        case TechSignal::Type::FULL_CAPACITY:
            if(currentVisitors >= capacity){
                std::cout << getName() << " is full. No more visitors accepted.\n";
            }
            break;

        case TechSignal::Type::POWER_FAILURE:
            active = false;
            demoRunning = false;

            std::cout << getName() << " stopped beacuse of a power failure.\n";
            break;
        
        case TechSignal::Type::EMERGENCY_PAUSE:
            active = false;
            demoRunning = false;

            std::cout << getName() << " stopped its demonstration for an emergency.\n";
            break;

        default:
            break;
    }
}

void AIDemoBooth::open(){
    this->isOpen = true;
    this->active = true;
    this->demoRunning = true;

    std::cout << getName() << " is now open. AI demonstration started.\n";
}

void AIDemoBooth::close(){
    this->isOpen = false;
    this->active = false;
    this->demoRunning = false;

    std::cout << getName() << " is now closed.\n";
}

void AIDemoBooth::reportStatus() const{
    std::cout << getName() << " | " << (isOpen ? "OPEN" : "CLOSED") << " | Visitors: " << currentVisitors << "/" << capacity << " | Demo: " << (demoRunning ? "RUNNING" : "STOPPED") << std::endl;
}

int AIDemoBooth::getCapacity() const{
    return this->capacity;
}