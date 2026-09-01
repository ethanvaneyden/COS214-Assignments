#include "AIZone.h"

AIZone::AIZone(EventComponent* parent) 
    : EventComposite("AI_Zone", parent), isOpen(false)
{}

void AIZone::add(EventComponent* component) {
    EventComposite::add(component);
}

void AIZone::remove(EventComponent* component) {
    EventComposite::remove(component);
}

void AIZone::open(){
    isOpen = true;
    for(auto child : children){
        if(child != nullptr)
            child->open();
    }
}

void AIZone::close(){
    this->isOpen = false;
    for (auto child : this->children){
        if(child != nullptr)
            child->close();
    }
}

std::string AIZone::getStatus() const{
    std::string output = "AI Zone: " + std::string(this->isOpen ? "OPEN" : "CLOSED") + "\n";
    for (auto child : this->children){
        if(child != nullptr)
            output += child->getStatus();
    }
    return output;
}


int AIZone::getCapacity() const{
    int totalCapacity = 0;
    for (auto child : this->children){
        if(child != nullptr)
            totalCapacity += child->getCapacity();
    }
    return totalCapacity;
}

int AIZone::getCurrentVisitors() const {
    int totalVisitors = 0;
    for (auto child : this->children){
        if(child != nullptr)
            totalVisitors += child->getCurrentVisitors();
    }
    return totalVisitors;
}

void AIZone::update(const TechSignal& signal){
    switch(signal.getType()){
        case TechSignal::Type::OPEN:
            isOpen = true;
            std::cout << "AI Zone is now OPEN.\n";
            transmit(signal);
            break;

        case TechSignal::Type::CLOSE:
            isOpen = false;
            std::cout << "AI Zone is now CLOSED.\n";
            transmit(signal);
            break;

        case TechSignal::Type::FULL_CAPACITY:
        case TechSignal::Type::SCHEDULE_CHANGE:
        case TechSignal::Type::POWER_FAILURE:
        case TechSignal::Type::EMERGENCY_PAUSE:
        case TechSignal::Type::RESUME:
            transmit(signal);
            break;

        default:
            break;
    }
}

int AIZone::enterVisitor(int visitors) {
    if (visitors <= 0 || !isOpen) {
        return 0;
    }

    int remaining = visitors;
    int totalAdmitted = 0;

    for (auto* child : children) {
        if (remaining <= 0) break;
        if (!child) continue;

        int admitted = child->enterVisitor(remaining);
        totalAdmitted += admitted;
        remaining -= admitted;
    }

    return totalAdmitted;
}

int AIZone::leaveVisitor(int visitors) {
    if (visitors <= 0) {
        return 0;
    }

    int remaining = visitors;
    int totalRemoved = 0;

    for (auto* child : children) {
        if (remaining <= 0) break;
        if (!child) continue;

        int removed = child->leaveVisitor(remaining);
        totalRemoved += removed;
        remaining -= removed;
    }

    return totalRemoved;
}