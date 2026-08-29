#ifndef SIGNALSUBSCRIBER_H
#define SIGNALSUBSCRIBER_H

// Forward declaration
class TechSignal;

/**
 * @class SignalSubscriber
 * @brief Pure Abstract Observer interface in the Observer design pattern.
 * 
 * Declares the update contract that all signal listeners (both Leaf units
 * and Composite event components) must fulfill to process events.
 */
class SignalSubscriber {
public:
    /**
     * @brief Construct a new Signal Subscriber object
     * */
    explicit SignalSubscriber() = default;
    /**
     * @brief Virtual destructor for SignalSubscriber.
     */
    virtual ~SignalSubscriber() = default;

    /**
     * @brief Pure virtual method to handle an incoming technical signal from a broadcaster.
     * @param signal The incoming TechSignal instance.
     */
    virtual void update(const TechSignal& signal) = 0;
};

#endif /* SIGNALSUBSCRIBER_H */