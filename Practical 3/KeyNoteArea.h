#ifndef KEYNOTEAREA_H
#define KEYNOTEAREA_H

#include <vector>
#include <atomic>
#include <string>
#include <chrono>
#include <mutex>
#include "EventComponent.h"

// Forward declarations
class TechSignal;
class BackgroundTimer;

/**
 * @class KeyNoteArea
 * @brief Leaf node component representing a Keynote presentation area on stage.
 * 
 * Manages local presenters via a background timer, handles domain status updates,
 * and resolves emergency staff contact details dynamically using its parent hierarchy pointer.
 */
class KeyNoteArea : public EventComponent {
public:
    /**
     * @brief Construct a new KeyNoteArea leaf object.
     * @param parent Pointer to the parent component in the composite hierarchy (default: nullptr).
     */
    explicit KeyNoteArea(EventComponent* parent = nullptr);

    /**
     * @brief Destructor that cleans up local timer dynamic allocations.
     */
    ~KeyNoteArea() override;

    /**
     * @brief Handles incoming technical signals to modify operational status and timers.
     * @param signal The TechSignal describing an event.
     */
    void update(const TechSignal& signal) override;

    /**
     * @brief Starts the background presenter rotation timer.
     */
    void startPresenterTimer();

    /**
     * @brief Stops the background presenter rotation timer.
     */
    void stopPresenterTimer();

    /**
     * @brief Pauses the background presenter rotation timer.
     */
    void pausePresenterTimer();

    /**
     * @brief Resumes the background presenter rotation timer.
     */
    void resumePresenterTimer();

    /**
     * @brief Advances to the next presenter in the rotation list.
     */
    void advancePresenter();

    /**
     * @brief Gets the name of the active presenter if the area is open.
     * @return std::string Name of active presenter or closure notification.
     */
    std::string getPresenter() const;

    /**
     * @brief Overrides Component method to return the operational status of the KeyNoteArea.
     * @return std::string Status description string.
     */
    std::string getStatus() const override;

private:
    mutable std::mutex stateMutex;        /**< Mutex protecting internal status and state */
    bool isOpen;                          /**< Indicates if the keynote area is operational */
    std::string status;                   /**< Current status message */

    std::vector<std::string> presenters;   /**< Schedule of presenters */
    std::atomic<size_t> presenterIndex{0}; /**< Thread-safe index for current presenter */

    BackgroundTimer* presenterTimer;      /**< Pointer to background timer for rotation */
    std::chrono::minutes presenterInterval; /**< Interval between presenter shifts */
};

#endif /* KEYNOTEAREA_H */