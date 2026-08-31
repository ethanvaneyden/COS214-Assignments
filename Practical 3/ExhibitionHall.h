#ifndef EXHIBITIONHALL_H
#define EXHIBITIONHALL_H

#include "SignalSubscriber.h"
#include "SignalBroadcaster.h"
#include "EventComponent.h"
#include "EventComposite.h"
#include "TechSignal.h"

#include <vector>
#include <iostream>

/**
 * @brief Represents the main exhibition hall.
 *
 * It is a Composite that has other components (SignalSubscriber)
 * It is also the Observer (SignalSubscriber) and the Subject
 * (SignalBroadcaster) for its children Onws its children but not its observers
*/
class ExhibitionHall : public EventComposite, public SignalBroadcaster {
  private:
        bool isOpen;

  public:
    /**
     * @brief Constructs an empty exhibition hall.
    */
    ExhibitionHall();

    /**
     * @brief Opens the exhibition hall and its components.
    */
    void open() override;

    /**
     * @brief Closes the exhibition hall and its components.
    */
    void close() override;

    /**
     * @brief Returns the total capacity of the exhibition hall.
     *
     * @return The total capacity.
    */
    int getCapacity() const override;

    /**
     * @brief Adds visitors to the exhibition hall.
     *
     * @param visitors The number of visitors to add.
     * @return true if the visitors were added successfully,
     *          false if the capacity would be exceeded.
    */
    int enterVisitor(int visitors) override;

    /**
     * @brief Removes visitors from the exhibition hall.
     *
     * @param visitors The number of visitors to remove.
     * @return true if the visitors were removed successfully,
     *          false if there are not enough visitors in the hall.
    */
    int leaveVisitor(int visitors) override;

    /**
     * @brief Gets the current number of visitors.
     *
     * @return The current number of visitors.
    */
    int getCurrentVisitors() const override;
    std::string getStatus() const override;

    /**
     * @brief Handles a received technology signal.
     *
     * @param signal The received signal.
    */
    void update(const TechSignal &signal) override;

    /**
     * @brief Destroys the exhibition hall and its components.
    */
    virtual ~ExhibitionHall() override = default;
};

#endif

