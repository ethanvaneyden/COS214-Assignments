#include "AIZone.h"

AIZone::AIZone(std::string name) 
    : EventComposite(name), isOpen(false)
{}

void AIZone::add(EventComponent* component){
    for(auto child : this->children){
        if(child == component) return; //prevents double addition
    }

    this->children.push_back(component);
}

void AIZone::remove(EventComponent* component){
    if(component == nullptr) return;

    for(auto it = children.begin(); it != children.end(); ++it){
        if(*it == component){
            children.erase(it);
            return; //not deleting as another parent could possible take ownership
        }
    }
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
    std::string output = "AI Zone: ";
    std::string temp = this->isOpen ? "OPEN" : "CLOSED";
    output += temp;
    output += "\n";

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

int AIZone::enterVisitor(int visitors){
    if(visitors <= 0 || !isOpen)
        return 0;

    int remaining = visitors;
    int accepted = 0;

    for(auto child : children){
        if(child == nullptr || remaining <= 0)
            continue;

        int admitted = child->enterVisitor(remaining);

        accepted += admitted;
        remaining -= admitted;
    }

    if(remaining > 0){
        std::cout << remaining << " visitor(s) could not enter " << getName() << " because the zone has insufficient capacity.\n";
    }

    return accepted;
}

int AIZone::leaveVisitor(int visitors){
    if(visitors <= 0)
        return 0;

    int remaining = visitors;
    int removed = 0;

    for(auto child : children){
        if(child == nullptr || remaining <= 0)
            continue;

        int departed = child->leaveVisitor(remaining);

        removed += departed;
        remaining -= departed;
    }

    if(remaining > 0){
        std::cout << remaining << " visitor(s) could not be removed from " << getName() << " because there were not enough visitors.\n";
    }

    return removed;
}



AIZone::~AIZone(){
    for (auto child : this->children){
        if(child != nullptr) 
            delete child;
    }
}
