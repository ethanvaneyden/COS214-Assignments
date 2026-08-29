#include "SignalSubscriber.h"

SignalSubscriber::SignalSubscriber(SignalSubscriber* parent) 
    : parent(parent) {}

void SignalSubscriber::setParent(SignalSubscriber* parentComponent) {
    parent = parentComponent;
}

SignalSubscriber* SignalSubscriber::getParent() const {
    return parent;
}

std::string SignalSubscriber::getStaff() const {
    if (parent) {
        return parent->getStaff();
    }
    return "No technician assigned in this zone.";
}