#ifndef SIGNALBROADCASTER_H
#define SIGNALBROADCASTER_H

#include <vector>
class SignalSubscriber;
class TechSignal;

/**
 * @brief This class is the subject. It will transmit any message down to its
 * children. It is owned by a composite object. Declares the contract for how to transmit a tech signal and keeps a record
 *
 */

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
  SignalBroadcaster() = default;
  /**
   * @brief Destroy the Signal Broadcaster object
   *
   */
  ~SignalBroadcaster() = default;
  /**
   * @brief Allows an observer to subscribe to this broadcaster
   *
   * @param subscriber
   */
  void subscribe(SignalSubscriber *subscriber);
  /**
   * @brief Allows an observer to unsubscribe to the broadcaster
   *
   * @param subscriber
   */
  void unsubscribe(SignalSubscriber *subscriber);
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