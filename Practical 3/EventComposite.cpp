#include "EventComposite.h"
#include "EventComponent.h"

void EventComposite::add(EventComponent *component){
    if(component == nullptr){
        return;
    }

    if(component == this){
        return;
    }

    if(component->getParent() != nullptr &&
        component->getParent() != this){
        return;
    }

    if(std::find(
            children.begin(),
            children.end(),
            component
        ) != children.end()){

        return;
    }

    children.push_back(component);

    component->setParent(this);

    broadcaster->subscribe(component);
}


void EventComposite::remove(EventComponent *component){
    if(component == nullptr){
        return;
    }

  
    auto it = std::find(
        children.begin(),
        children.end(),
        component
    );

    if(it != children.end()){

        
    (*it)->setParent(nullptr);
        broadcaster->unsubscribe(component);
        children.erase(it);
    }
}

std::string EventComposite::getDisplayDetails() const
{
  return getName() + " (" + getStaff() + ")";  
}

EventComposite::EventComposite(std::string name, EventComponent *parent)
    : EventComponent(name, parent), broadcaster(std::unique_ptr<SignalBroadcaster>(new SignalBroadcaster())) {}

bool EventComposite::hasChildren() const{

    return !children.empty();
}
