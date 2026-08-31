#ifndef AIZONE_H
#define AIZONE_H

#include "SignalSubscriber.h"
#include "SignalBroadcaster.h"
#include "EventComponent.h"
#include "EventComposite.h"
#include "TechSignal.h"

#include <vector>
#include <iostream>

/**
 * @brief Represents the AI zone.
 * 
 * It is a composite that will have RoboticsBooth and AIDemoBooth at the start
 * It is also an Observer (SignalSubscriber) and Subject to it's children (SignalBroadcaster)
 * It owns its children as the composite
 * but does not own its observers
 */
class AIZone : public EventComposite, public SignalBroadcaster {
    private:
        bool isOpen;

    public:
        /**
         * @brief Constructs an AI zone.
         *
         * @param name Name of the zone.
        */
        AIZone(std::string name);

        /**
         * @brief Adds a component to the AI zone.
         *
         * @param component The component to add.
        */
        void add(EventComponent* component) override;

        /**
         * @brief Removes a component from the AI zone.
         *
         * @param component The component to remove.
        */
        void remove(EventComponent* component) override;

        /**
         * @brief Opens the AI zone and its components.
        */
        void open() override;

        /**
         * @brief Closes the AI zone and its components.
        */
        void close() override;

        /**
         * @brief Reports the status of the AI zone.
        */
        std::string getStatus() const override;

        /**
         * @brief Returns the total capacity of the AI zone.
         *
         * @return The total capacity.
        */
        int getCapacity() const override;

        /**
         * @brief Handles a received technology signal.
         *
         * @param signal The received signal.
        */
        void update(const TechSignal& signal) override;

        /**
         * @brief Distributes incoming visitors among the zone's children.
         *
         * The zone attempts to distribute the requested visitors sequentially
         * among its child components. Each child decides how many visitors it
         * can actually accept through polymorphic dispatch.
         *
         * Visitors that cannot be accommodated by one child are passed to the
         * next child. This continues until all visitors have been admitted or
         * all children have been given an opportunity to accept them.
         *
         * @param visitors Number of visitors attempting to enter the zone.
         * @return The total number of visitors actually admitted into the zone.
        */
        int enterVisitor(int visitors);

        /**
         * @brief Distributes departing visitors among the zone's children.
         *
         * The zone asks each child to remove as many visitors as possible,
         * continuing with the remaining number until all requested visitors
         * have been removed or all children have been checked.
         *
         * @param visitors Number of visitors attempting to leave the zone.
         * @return The total number of visitors actually removed from the zone.
        */
        int leaveVisitor(int visitors);

        /**
         * @brief Destroys the AI zone and its components.
        */
        ~AIZone() override;
};

#endif
