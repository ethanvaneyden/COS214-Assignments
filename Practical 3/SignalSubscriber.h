#ifndef SIGNALSUBSCRIBER_H
#define SIGNALSUBSCRIBER_H

class TechSignal;

class SignalSubscriber {
public:
  /**
   * @brief Constructs a new signal subscriber.
   */
  SignalSubscriber() = default;

  /**
   * @brief Destroys the signal subscriber.
   */
  virtual ~SignalSubscriber() = default;

  /**
   * @brief Handles a signal received from a broadcaster.
   *
   * @param signal The signal received from the broadcaster.
   */
  virtual void update(const TechSignal& signal) = 0;

  /**
   * @brief Adds a subscriber.
   *
   * @param subscriber The subscriber to add.
   */
  virtual void add(SignalSubscriber* subscriber) = 0;
};

#endif