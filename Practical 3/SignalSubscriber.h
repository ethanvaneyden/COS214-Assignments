#ifndef SIGNALSUBSCRIBER_H
#define SIGNALSUBSCRIBER_H

class TechSignal;

class SignalSubscriber
{
public:
    SignalSubscriber() = default;
    virtual ~SignalSubscriber() = default;
    virtual void update(const TechSignal &signal) = 0;
};

#endif