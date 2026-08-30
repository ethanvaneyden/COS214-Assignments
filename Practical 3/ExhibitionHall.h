#ifndef EXHIBITIONHALL_H
#define EXHIBITIONHALL_H

#include "EventComposite.h"
#include <vector>

/**
 * @brief Represents the main exhibition hall.
 *
 * It is a Composite that has other components (SignalSubscriber)
 * It is also the Observer (SignalSubscriber) and the Subject
 * (SignalBroadcaster) for its children Onws its children but not its observers
 */
class ExhibitionHall : public EventComposite {
public:
  /**
   * @brief Constructs an empty exhibition hall.
   */
  ExhibitionHall();

  /**
   * @brief Opens the exhibition hall and its components.
   */
  void open() override;

  /**
   * @brief Closes the exhibition hall and its components.
   */
  void close() override;

  /**
   * @brief Reports the status of the exhibition hall.
   */
  void reportStatus() const override;

  /**
   * @brief Returns the total capacity of the exhibition hall.
   *
   * @return The total capacity.
   */
  int getCapacity() const override;

  /**
   * @brief Handles a received technology signal.
   *
   * @param signal The received signal.
   */
  void update(const TechSignal &signal) override;

  /**
   * @brief Destroys the exhibition hall and its components.
   */
  ~ExhibitionHall() override;
};

#endif
