#ifndef MAINSTAGE_H
#define MAINSTAGE_H

#include <vector>
#include <atomic>
#include <string>
#include <chrono>
#include "SignalSubscriber.h"

// Forward declarations
class TechSignal;
class BackgroundTimer;
class Technician;

/**
 * @class MainStage
 * @brief Represents a Composite node in the hierarchy that holds child components
 *        and manages active technician rotations.
 */
class MainStage : public SignalSubscriber {
public:
    /**
     * @brief Construct a new MainStage composite object.
     * @param parent Pointer to the parent component in the hierarchy (default: nullptr).
     */
    explicit MainStage(SignalSubscriber* parent = nullptr);

    /**
     * @brief Destructor that cleans up dynamic timer allocations.
     */
    ~MainStage() override;

    /**
     * @brief Broadcasts the incoming signal to all registered child components.
     * @param signal The TechSignal to propagate.
     */
    void update(const TechSignal &signal) override;

    /**
     * @brief Adds a child subscriber to this composite node and assigns itself as parent.
     * @param subscriber Pointer to the child subscriber to add.
     */
    void add(SignalSubscriber* subscriber) override;

    /**
     * @brief Removes a child subscriber from this composite node.
     * @param subscriber Pointer to the child subscriber to remove.
     */
    void remove(SignalSubscriber* subscriber) override;

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
     * @brief Overrides Component method to provide current technician on duty at this level.
     * @return `std::string` Information of current technician, or delegates to parent if empty.
     */
    std::string getStaff() const override;


    /**
     * @brief Overrides Component method to recursively query the current operational status message of the MainStage.
     * @return `std::string` Name of Stage and status of subscribers.
     */
    std::string getStatus() const override;
    
private:
    std::vector<SignalSubscriber*> subscribers; /**< Child components managed by this composite */
    std::vector<Technician> staff;               /**< Roster of technicians assigned to stage */
    std::atomic<size_t> staffIndex{0};           /**< Thread-safe index for current staff member */
    
    BackgroundTimer* staffTimer;                 /**< Pointer to background timer thread */
    std::chrono::minutes staffInterval;          /**< Time interval between staff rotations */
};

#endif /* MAINSTAGE_H */