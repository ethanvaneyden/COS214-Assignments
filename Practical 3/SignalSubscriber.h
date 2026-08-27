#ifndef SIGNALSUBSCRIBER_H
#define SIGNALSUBSCRIBER_H

class TechSignal;

class SignalSubscriber {
public:
  /**
   * @brief Construct a new Signal Subscriber object
   *
   */
  SignalSubscriber() = default;
  /**
   * @brief Destroy the Signal Subscriber object
   *
   */
  virtual ~SignalSubscriber() = default;
  /**
   * @brief Receives a signal from its subscribed broadcaster do
   * something with it
   *
   * @param signal
   */
  virtual void update(const TechSignal &signal) = 0;
};

#endif