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

    /*
     * FIX 1:
     * Do not allow a component to become its own parent.
     *
     * Without this check:
     *
     *     component >> component;
     *
     * could try to add the component to itself.
     */
    if(&child == &newParent){
        return newParent;
    }


    /*
     * FIX 2:
     * Do not allow a component to be moved underneath one of
     * its own children.
     *
     * For example, if the hierarchy is:
     *
     * Main Hall
     *     |
     *     Main Stage
     *         |
     *         Keynote Area
     *
     * we should not allow:
     *
     *     Main Stage >> Keynote Area
     *
     * because this would create a circular hierarchy.
     *
     * We walk up from newParent and check whether we eventually
     * reach child.
     */
    EventComponent *current = &newParent;

    while(current != nullptr){

        if(current == &child){
            return newParent;
        }

        current = current->getParent();
    }


    /*
     * FIX 3:
     * Remove the child from its old parent before adding it
     * to the new parent.
     *
     * This keeps the hierarchy consistent and prevents the
     * child from appearing under two different parents.
     */
    if(child.parent){
        child.parent->remove(&child);
    }


    /*
     * Add the child to the new parent.
     *
     * EventComposite::add() is responsible for setting the
     * child's parent pointer and subscribing it to the
     * parent's broadcaster.
     */
    newParent.add(&child);

    return newParent;
}


/**
 * @brief Returns the name of this component.
 */
std::string EventComponent::getName() const{
    return name;
}
