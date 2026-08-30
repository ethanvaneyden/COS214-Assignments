#ifndef DEMOAREA_H
#define DEMOAREA_H

#include "EventLeaf.h"
#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>

// Forward declarations
class TechSignal;
class BackgroundTimer;

/**
 * @class DemoArea
 * @brief Leaf node component representing the interactive demonstration area.
 * 
 * Manages live demonstration schedules, safety locks, visitor tracking, and hands-on interaction permissions.
 */
class DemoArea : public EventLeaf {
public:
    /**
     * @brief Construct a new DemoArea leaf object.
     * @param parent Pointer to the parent component in the composite hierarchy (default: nullptr).
     */
    explicit DemoArea(EventComponent* parent = nullptr);

    /**
     * @brief Destructor that cleans up local timer dynamic allocations.
     */
    ~DemoArea() override;

    /**
     * @brief Handles incoming technical signals to modify operational status and safety states.
     * @param signal The TechSignal describing an event.
     */
    void update(const TechSignal& signal) override;

    // Component lifecycle and capacity interface methods
    void open() override;
    void close() override;
    void reportStatus() const override;
    int getCapacity() const override;
    int enterVisitor(int visitors) override;
    int leaveVisitor(int visitors) override;
    int getCurrentVisitors() const override;

    /**
     * @brief Starts the background product demonstration rotation timer.
     */
    void startDemoTimer();

    /**
     * @brief Stops the background product demonstration rotation timer.
     */
    void stopDemoTimer();

    /**
     * @brief Pauses the background product demonstration rotation timer.
     */
    void pauseDemoTimer();

    /**
     * @brief Resumes the background product demonstration rotation timer.
     */
    void resumeDemoTimer();

    /**
     * @brief Advances to the next product demonstration in the schedule.
     */
    void advanceDemo();

    /**
     * @brief Toggles whether audience hands-on testing is currently permitted.
     * @param allowed True to allow hands-on testing, false otherwise.
     */
    void setHandsOnAllowed(bool allowed);

    /**
     * @brief Checks if hands-on testing is allowed for the active demo.
     * @return true If attendees can test the hardware.
     */
    bool isHandsOnAllowed() const;

    /**
     * @brief Checks if demo equipment has passed safety inspection.
     * @return true If equipment is verified safe.
     */
    bool isEquipmentReady() const;

    /**
     * @brief Gets the name of the active product demonstration.
     * @return std::string Name of active demo or closure notification.
     */
    std::string getCurrentDemo() const;

    /**
     * @brief Gets the technical requirement specs for the active demo.
     * @return std::string Specs string for the active demo.
     */
    std::string getDemoDetails() const;

    /**
     * @brief Overrides Component method to return operational status and safety state.
     * @return std::string Status description string.
     */
    std::string getStatus() const override;

private:
    mutable std::mutex stateMutex;        /**< Mutex protecting internal status and safety state */
    bool isOpen;                          /**< Indicates if the demo area is operational */
    bool handsOnAllowed;                  /**< Indicates if attendee hands-on testing is active */
    bool equipmentReady;                  /**< Indicates if demo equipment safety checks passed */
    int capacity;                         /**< Maximum capacity of visitors allowed */
    int currentVisitors;                  /**< Current active count of visitors */
    std::string status;                   /**< Current status message */

    std::vector<std::string> demoSchedule; /**< Schedule of live product demonstrations */
    std::vector<std::string> demoSpecs;    /**< Technical specs matching each demonstration */
    std::atomic<size_t> demoIndex{0};     /**< Thread-safe index for current demo */

    BackgroundTimer* demoTimer;           /**< Pointer to background timer for rotation */
    std::chrono::minutes demoInterval;    /**< Interval between scheduled demonstrations */
};

#endif /* DEMOAREA_H */