#include "ExhibitionHall.h"

ExhibitionHall::ExhibitionHall()
    : EventComposite("Main_Exhibition_Hall"), isOpen(false) 
{}


void ExhibitionHall::open(){
    isOpen = true;

    std::cout << getName() << " is now OPEN.\n";

    for(EventComponent* child : children){
        if(child != nullptr){
            child->open();
        }
    }
}


void ExhibitionHall::close(){
    isOpen = false;

    std::cout << getName() << " is now CLOSED.\n";

    for(EventComponent* child : children){
        if(child != nullptr){
            child->close();
        }
    }
}


int ExhibitionHall::getCapacity() const{
    int totalCapacity = 0;

    for(EventComponent* child : children){
        if(child != nullptr){
            totalCapacity += child->getCapacity();
        }
    }

    return totalCapacity;
}


int ExhibitionHall::enterVisitor(int visitors){
    if(visitors <= 0 || !isOpen){
        return 0;
    }

    int remaining = visitors;
    int accepted = 0;

    for(EventComponent* child : children){
        if(child == nullptr || remaining <= 0){
            continue;
        }

        int admitted = child->enterVisitor(remaining);

        accepted += admitted;
        remaining -= admitted;
    }

    if(remaining > 0){
        std::cout << remaining << " visitor(s) could not enter " << getName() << " because there was insufficient capacity.\n";
    }

    return accepted;
}


int ExhibitionHall::leaveVisitor(int visitors){
    if(visitors <= 0){
        return 0;
    }

    int remaining = visitors;
    int removed = 0;

    for(EventComponent* child : children){
        if(child == nullptr || remaining <= 0){
            continue;
        }

        int departed = child->leaveVisitor(remaining);

        removed += departed;
        remaining -= departed;
    }

    if(remaining > 0){
        std::cout << remaining << " visitor(s) could not be removed from " << getName() << " because there were not enough visitors.\n";
    }

    return removed;
}


int ExhibitionHall::getCurrentVisitors() const{
    int totalVisitors = 0;

    for(EventComponent* child : children){
        if(child != nullptr){
            totalVisitors += child->getCurrentVisitors();
        }
    }

    return totalVisitors;
}


std::string ExhibitionHall::getStatus() const{
    std::string output;

    output += "----- EXHIBITION HALL -----\n";
    output += "Status: ";
    output += isOpen ? "OPEN\n" : "CLOSED\n";

    for(EventComponent* child : children){
        if(child != nullptr){
            output += child->getStatus();
        }
    }

    return output;
}


void ExhibitionHall::update(const TechSignal& signal){
    switch(signal.getType()){
        case TechSignal::Type::OPEN:
            isOpen = true;

            std::cout << getName()
                      << " received OPEN signal.\n";

            transmit(signal);
            break;

        case TechSignal::Type::CLOSE:
            isOpen = false;

            std::cout << getName()
                      << " received CLOSE signal.\n";

            transmit(signal);
            break;

        case TechSignal::Type::FULL_CAPACITY:
        case TechSignal::Type::SCHEDULE_CHANGE:
        case TechSignal::Type::POWER_FAILURE:
        case TechSignal::Type::EMERGENCY_PAUSE:
        case TechSignal::Type::RESUME:
        case TechSignal::Type::NETWORK_FAILURE:
            transmit(signal);
            break;

        case TechSignal::Type::UNKNOWN:
        default:
            break;
    }
}