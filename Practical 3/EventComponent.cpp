#include "EventComponent.h"

EventComponent::EventComponent(EventComponent* parentComponent)
    : parent(parentComponent) {}

void EventComponent::setParent(EventComponent* parentComponent) {
    parent = parentComponent;
}

EventComponent* EventComponent::getParent() const {
    return parent;
}

std::string EventComponent::getStaff() const {
    if (parent) {
        return parent->getStaff();
    }
    return "No technician assigned in this zone.";
}

EventComponent& operator>>(EventComponent& child, EventComponent& newParent) {
    if (&child == &newParent) {
        return newParent;
    }

    if (child.parent) {
        child.parent->remove(&child);
    }

    newParent.add(&child);
    return newParent;
}