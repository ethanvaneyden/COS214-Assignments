#ifndef SIGNALBROADCASTER_H
#define SIGNALBROADCASTER_H

#include <vector>
class SignalSubscriber;
class TechSignal;

class SignalBroadcaster {
protected:
  std::vector<SignalSubscriber *> subscribers;

public:
  /**
   * @brief Construct a new Signal Broadcaster object
   *
   * @param subscribers
   */
  SignalBroadcaster(const std::vector<SignalSubscriber *> &subscribers);
  /**
   * @brief Construct a new Signal Broadcaster object
   *
   */
  SignalBroadcaster();
  /**
   * @brief Destroy the Signal Broadcaster object
   *
   */
  virtual ~SignalBroadcaster() = default;
  /**
   * @brief Allows an observer to subscribe to this broadcaster
   *
   * @param subscriber
   */
  virtual void subscribe(SignalSubscriber *subscriber);
  /**
   * @brief Allows an observer to unsubscribe to the broadcaster
   *
   * @param subscriber
   */
  virtual void unsubscribe(SignalSubscriber *subscriber);
  /**
   * @brief Transmits the command to all signal subscribers
   *
   * @param signal
   */
  void transmit(const TechSignal &signal);
  /**
   * @brief Clears the list of subscribers
   *
   */
  void clearSubscribers();
  /**
   * @brief Returns the number of current subscribers
   *
   * @return size_t
   */
  size_t getSubscriberCount() const;
};
#endif