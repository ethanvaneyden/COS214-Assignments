#include "EventLeaf.h"

EventLeaf::EventLeaf(std::string name, EventComponent *parent)
    : EventComponent(name, parent) {}

std::string EventLeaf::getDisplayDetails() const
{
    return getName();
}
