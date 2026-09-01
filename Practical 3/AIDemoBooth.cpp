#include "AIDemoBooth.h"

AIDemoBooth::AIDemoBooth(int capacity, std::string name)
    : EventLeaf(name), isOpen(false), active(false), capacity(capacity), currentVisitors(0), requiresNetwork(true), demoRunning(false)   
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

        case TechSignal::Type::SCHEDULE_CHANGE:
            std::cout << getName() << " received a schedule change: " << signal.getMessage() << std::endl;
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

        case TechSignal::Type::RESUME:
            if(isOpen){
                active = true;
                demoRunning = true;

                std::cout << getName() << " resumed its AI demonstration.\n";
            }
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

std::string AIDemoBooth::getStatus() const{
    std::string output = "";
    std::string temp = getName();
    output += temp + " | ";

    temp = isOpen ? "OPEN" : "CLOSED";
    output += temp + " | Visitors: ";

    temp = std::to_string(currentVisitors);
    output += temp + "/";

    temp = std::to_string(capacity);
    output += temp + " | Demo: ";

    temp = demoRunning ? "RUNNING" : "STOPPED";
    output += temp + "\n";

    return output;
}

void AIDemoBooth::reportStatus() const{
    std::cout << getStatus();
}

int AIDemoBooth::getCurrentVisitors() const{
    return currentVisitors;
}

int AIDemoBooth::getCapacity() const{
    return this->capacity;
}

int AIDemoBooth::enterVisitor(int visitors){
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

        TechSignal signal(TechSignal::Type::FULL_CAPACITY, "AI Demo Booth has reached full capacity.");
        update(signal);
        return 0;
    }

    this->currentVisitors += accepted;

    std::cout << accepted << " visitor(s) entered " << getName() << ". Visitors: " << currentVisitors << "/" << capacity << "\n";

    if(currentVisitors >= capacity){
        TechSignal signal(TechSignal::Type::FULL_CAPACITY, "AI Demo Booth has reached full capacity.");
        update(signal);
    }

    return accepted;
}

int AIDemoBooth::leaveVisitor(int visitors){
    if(visitors <= 0)
        return 0;

    int removed = (visitors < this->currentVisitors) ? visitors : currentVisitors;
    this->currentVisitors -= removed;
    std::cout << removed << " visitor(s) left " << getName() << ". Visitors: " << currentVisitors << "/" << capacity << "\n";

    return removed;
}
