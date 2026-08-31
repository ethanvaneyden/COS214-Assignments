#ifndef EVENTCOMPOSITE_H
#define EVENTCOMPOSITE_H

#include "EventComponent.h"
#include "SignalBroadcaster.h"
#include "TechSignal.h"
#include <algorithm>
#include <memory>
#include <vector>

/**
 * @brief This is the class that represents a composite in the hierachy. It has
 * a list of children and a broadcaster object.
 *
 *
 */
class EventComposite : public EventComponent {

protected:
  std::vector<EventComponent *> children;
  std::unique_ptr<SignalBroadcaster> broadcaster;

public:
  /**
   * @brief Adds a component to the hieracy and also subscribes it to the
   * broadcaster.
   *
   *
   * @param component
   */
  void add(EventComponent *component) override;
  /**
 * @brief Removes a component from the hierachy and unsubscribes it
 from the broadcaster.
 *
 * @param component
 */
  void remove(EventComponent *component) override;

  /**
   * @brief Checks if composite has any children
   * 
   * @return true 
   * @return false 
   */
  bool hasChildren() const override;

  virtual ~EventComposite() = default;

protected:
  EventComposite(std::string name, EventComponent *parent = nullptr);
};

#endif