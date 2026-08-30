#include "EventComposite.h"
#include "EventComponent.h"

void EventComposite::add(EventComponent *component) {
  if (component && std::find(children.begin(), children.end(), component) ==
                       children.end()) {
    children.push_back(component);
    component->setParent(this);
    broadcaster->subscribe(component);
  }
}

void EventComposite::remove(EventComponent *component) {
  auto it = std::find(children.begin(), children.end(), component);
  if (it != children.end()) {
    (*it)->setParent(nullptr);
    broadcaster->unsubscribe(component);
    children.erase(it);
  }
}

EventComposite::EventComposite(std::string name, EventComponent *parent)
    : EventComponent(name, parent),
      broadcaster(std::make_unique<SignalBroadcaster>()) {}

EventComposite::~EventComposite() {
  for (EventComponent *child : children) {
    delete child;
  }

  children.clear();
}