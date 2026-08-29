#ifndef MAINSTAGE_H
#define MAINSTAGE_H

#include <vector>
#include <atomic>
#include <string>
#include <chrono>
#include "EventComponent.h"
#include "SignalBroadcaster.h"

// Forward declarations
class TechSignal;
class BackgroundTimer;
class Technician;

/**
 * @class MainStage
 * @brief Composite node in the hierarchy that holds child components
 *        and manages active technician rotations.
 */
class MainStage : public EventComponent, public SignalBroadcaster {
public:
    /**
     * @brief Construct a new MainStage composite object.
     * @param parent Pointer to the parent component in the hierarchy (default: nullptr).
     */
    explicit MainStage(EventComponent* parent = nullptr);

    /**
     * @brief Destructor that cleans up dynamic timer allocations.
     */
    ~MainStage() override;

    /**
     * @brief Receives a signal and broadcasts it to all child subscribers.
     * @param signal The TechSignal to propagate down the tree.
     */
    void update(const TechSignal& signal) override;

    /**
     * @brief Adds a child component to this stage and registers it as a signal subscriber.
     * @param component Pointer to the child EventComponent to add.
     */
    void add(EventComponent* component) override;

    /**
     * @brief Removes a child component from this stage and unregisters it from broadcast signals.
     * @param component Pointer to the child EventComponent to remove.
     */
    void remove(EventComponent* component) override;

    /**
     * @brief Starts the background rotation timer for technical staff.
     */
    void startStaffTimer();

    /**
     * @brief Stops the background rotation timer for technical staff.
     */
    void stopStaffTimer();

    /**
     * @brief Advances the technician index to the next staff member in rotation.
     */
    void advanceStaff();

    /**
     * @brief Overrides Component method to provide the current technician on duty.
     * @return std::string Information of current technician, or delegates to parent.
     */
    std::string getStaff() const override;

    /**
     * @brief Recursively collects and formats the status of all child components.
     * @return std::string Summary status string for the stage and its sub-components.
     */
    std::string getStatus() const override;

private:
    std::vector<EventComponent*> children; /**< Collection of child components */
    std::vector<Technician> staff;          /**< Roster of technicians assigned to stage */
    std::atomic<size_t> staffIndex{0};      /**< Thread-safe index for current staff member */

    BackgroundTimer* staffTimer;            /**< Background timer thread for staff rotation */
    std::chrono::minutes staffInterval;     /**< Time interval between staff rotations */
};

#endif /* MAINSTAGE_H */