#ifndef EVENTLEAF_H
#define EVENTLEAF_H

#include "EventComponent.h"

/**
 * @brief The interface representing the leaves of the hierachy
 *
 */

class EventLeaf : public EventComponent {
protected:
  /**
   * @brief Constructs a new EventLeaf.
   *
   * @param name Name of the leaf component.
   * @param parent Parent component in the hierarchy.
   */
  EventLeaf(std::string name, EventComponent *parent = nullptr);
  std::string lastMessage;
public:
  /**
   * @brief Virtual destructor for EventLeaf.
   */
  ~EventLeaf() override = default;

  std::string getDisplayDetails() const override;
};

#endif