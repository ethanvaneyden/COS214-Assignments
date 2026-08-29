#ifndef SIGNALSUBSCRIBER_H
#define SIGNALSUBSCRIBER_H

#include <string>

// Forward declaration
class TechSignal;

/**
 * @class SignalSubscriber
 * @brief Base Component interface in the Composite architecture and Observer participant.
 * 
 * Declares common operations for both leaf units (booths, areas) and composite
 * nodes (zones, stages). Provides hierarchical parent-child linking to allow
 * contextual traversal, such as looking up on-duty technicians up the tree.
 */
class SignalSubscriber {
public:
    /**
     * @brief Construct a new SignalSubscriber component.
     * @param parent Pointer to the parent component in the hierarchy (default: nullptr).
     */
    explicit SignalSubscriber(SignalSubscriber* parent = nullptr);

    /**
     * @brief Virtual destructor for SignalSubscriber.
     */
    virtual ~SignalSubscriber() = default;

    /**
     * @brief Pure virtual method to process technical signals received from a broadcaster.
     * @param signal The incoming TechSignal instance.
     */
    virtual void update(const TechSignal& signal) = 0;

    /**
     * @brief Adds a child component to this node (Composite pattern interface).
     * @param subscriber Pointer to the child SignalSubscriber to add.
     * @note Default implementation is a no-op for leaf components.
     */
    virtual void add(SignalSubscriber* subscriber) {}

    /**
     * @brief Removes a child component from this node (Composite pattern interface).
     * @param subscriber Pointer to the child SignalSubscriber to remove.
     * @note Default implementation is a no-op for leaf components.
     */
    virtual void remove(SignalSubscriber* subscriber) {}

    /**
     * @brief Sets the parent component in the hierarchy.
     * @param parentComponent Pointer to the new parent component.
     */
    void setParent(SignalSubscriber* parentComponent);

    /**
     * @brief Gets the parent component in the hierarchy.
     * @return SignalSubscriber* Pointer to the parent component, or nullptr if root.
     */
    SignalSubscriber* getParent() const;

    /**
     * @brief Recursively queries the tree hierarchy to find the on-duty technician.
     * @return `std::string` Name/contact info of technician on duty, or fallback message.
     */
    virtual std::string getStaff() const;

    /**
     * @brief Pure virtual method that recursively queries the tree hierarchy to find the status of the area/zone.
     * @return `std::string` Status description of the subscriber
     */
    virtual std::string getStatus() const = 0;

private:
    SignalSubscriber* parent; /**< Pointer to parent node in composite hierarchy */
};

#endif /* SIGNALSUBSCRIBER_H */