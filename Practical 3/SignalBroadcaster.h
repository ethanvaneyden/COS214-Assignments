#ifndef SIGNALBROADCASTER_H
#define SIGNALBROADCASTER_H

#include <vector>
class SignalSubscriber;
class TechSignal;

class SignalBroadcaster
{
protected:
    std::vector<SignalSubscriber *> subscribers;

public:
    SignalBroadcaster(const std::vector<SignalSubscriber *> &subscribers);
    SignalBroadcaster();
    virtual ~SignalBroadcaster() = default;
    virtual void subscribe(SignalSubscriber *subscriber);
    virtual void unsubscribe(SignalSubscriber *subscriber);
    void transmit(const TechSignal &signal);
    void clearSubscribers();
    size_t getSubscriberCount() const;
};
#endif