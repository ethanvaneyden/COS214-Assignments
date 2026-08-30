#ifndef EVENTCOMPOSITE_H
#define EVENTCOMPOSITE_H

#include "EventComponent.h"
#include "SignalBroadcaster.h"
#include "TechSignal.h"
#include <algorithm>
#include <memory>
#include <vector>
class EventComposite : public EventComponent {

protected:
  std::vector<EventComponent *> children;
  std::unique_ptr<SignalBroadcaster> broadcaster;

public:
  void add(EventComponent *component) override;
  void remove(EventComponent *component) override;
};

#endif