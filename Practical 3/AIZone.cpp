#include "AIZone.h"

AIZone::AIZone(std::string name) 
    : EventComponent(name), isOpen(false)
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

void AIZone::reportStatus() const{
    std::cout << "AI Zone: " << (this->isOpen ? "OPEN" : "CLOSED") << std::endl;

    for (auto child : this->children){
        if(child != nullptr)
            child->reportStatus();
    }
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
    //still decideing on what to change,,,
}

AIZone::~AIZone(){
    for (auto child : this->children){
        if(child != nullptr) 
            delete child;
    }
}
