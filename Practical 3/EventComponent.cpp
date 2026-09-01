#include "EventComponent.h"

/**
 * @brief Constructs an EventComponent.
 *
 * The component starts with the supplied name and parent.
 */
EventComponent::EventComponent(std::string name, EventComponent *parentComponent)
    : name(name), parent(parentComponent){}


/**
 * @brief Sets the parent of this component.
 *
 * This is used when a component is added to or removed from
 * an EventComposite.
 */
void EventComponent::setParent(EventComponent *parentComponent){
    parent = parentComponent;
}


/**
 * @brief Returns the parent of this component.
 */
EventComponent *EventComponent::getParent() const{
    return parent;
}


/**
 * @brief Gets the technician assigned to this component.
 *
 * If this component does not have its own technician, the request
 * moves up the hierarchy until a parent provides one.
 *
 * If there is no parent with a technician, a default message is returned.
 */
std::string EventComponent::getStaff() const{
    if(parent){
        return parent->getStaff();
    }

    return "No technician assigned in this zone.";
}


/**
 * @brief Moves a component to a new parent.
 *
 * Example:
 *
 *     keynote >> mainStage;
 *
 * This removes the keynote area from its old parent and adds it
 * to the new parent.
 */
EventComponent &operator>>(EventComponent &child, EventComponent &newParent){


    if(&child == &newParent){
        return newParent;
    }

    EventComponent *current = &newParent;

    while(current != nullptr){

        if(current == &child){
            return newParent;
        }

        current = current->getParent();
    }

    if(child.parent){
        child.parent->remove(&child);
    }

    newParent.add(&child);

    return newParent;
}


/**
 * @brief Returns the name of this component.
 */
std::string EventComponent::getName() const{
    return name;
}
