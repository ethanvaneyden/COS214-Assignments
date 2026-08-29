#ifndef AIZONE_H
#define AIZONE_H

#include "SignalSubscriber.h"
#include "SignalBroadcaster.h"
#include "EventComponent.h"

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
class AIZone : public EventComponent, public SignalBroadcaster {
    private:
        std::vector<EventComponent*> children;
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
        void reportStatus() const override;

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
         * @brief Destroys the AI zone and its components.
        */
        ~AIZone() override;
};

#endif
