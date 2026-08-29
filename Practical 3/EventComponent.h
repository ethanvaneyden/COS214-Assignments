#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>
#include "SignalSubscriber.h"

/**
 * @class EventComponent
 * @brief Base Component interface in the Composite pattern, inheriting from SignalSubscriber.
 * 
 * Unifies composite containers and individual operational leaves under a shared interface.
 * Provides hierarchical parent-child linking to support upward contextual queries (such as
 * finding on-duty staff) and stream-based relocation.
 */
class EventComponent : public SignalSubscriber {
public:
    /**
     * @brief Construct a new EventComponent object.
     * @param parentComponent Pointer to the parent component in the hierarchy (default: nullptr).
     */
    explicit EventComponent(EventComponent* parentComponent = nullptr);

    /**
     * @brief Virtual destructor for EventComponent.
     */
    ~EventComponent() override = default;

    /**
     * @brief Adds a child component to this node (Composite pattern interface).
     * @param component Pointer to the child EventComponent to add.
     * @note Default implementation is a no-op for leaf nodes.
     */
    virtual void add(EventComponent* component) {}

    /**
     * @brief Removes a child component from this node (Composite pattern interface).
     * @param component Pointer to the child EventComponent to remove.
     * @note Default implementation is a no-op for leaf nodes.
     */
    virtual void remove(EventComponent* component) {}

    /**
     * @brief Sets the parent component in the hierarchy.
     * @param parentComponent Pointer to the new parent component.
     */
    void setParent(EventComponent* parentComponent);

    /**
     * @brief Gets the parent component in the hierarchy.
     * @return EventComponent* Pointer to the parent component, or nullptr if root.
     */
    EventComponent* getParent() const;

    /**
     * @brief Recursively queries the parent hierarchy to find the on-duty technician.
     * @return std::string Contact details of on-duty staff, or fallback message.
     */
    virtual std::string getStaff() const;

    /**
     * @brief Pure virtual method querying the status of the component or its subtree.
     * @return std::string Operational status description.
     */
    virtual std::string getStatus() const = 0;

    /**
     * @brief Stream operator overload to relocate a component to a new parent zone.
     * @param child The component being moved.
     * @param newParent The target composite parent component.
     * @return EventComponent& Reference to the target parent for chaining.
     */
    friend EventComponent& operator>>(EventComponent& child, EventComponent& newParent);

private:
    EventComponent* parent; /**< Pointer to parent node in composite hierarchy */
};

#endif /* EVENTCOMPONENT_H */