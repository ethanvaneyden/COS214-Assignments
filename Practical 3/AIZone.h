#ifndef AIZONE_H
#define AIZONE_H

#include "SignalSubscriber.h"
#include "SignalBroadcaster.h"
#include <vector>

/**
 * @brief Composite representing the AI zone.
 */
class AIZone : public SignalSubscriber, public SignalBroadcaster {
    private:
        std::vector<SignalSubscriber*> components;

    public:
        /**
         * @brief Constructs an empty AI zone.
        */
        AIZone();

        /**
         * @brief Destroys the AI zone and its components.
        */
        ~AIZone() override;

        /**
         * @brief Adds a component to the AI zone.
         *
         * @param component The component to add.
        */
        void add(SignalSubscriber* component) override;

        /**
         * @brief Removes a component from the AI zone.
         *
         * @param component The component to remove.
        */
        void remove(SignalSubscriber* component) override;

        /**
         * @brief Opens the AI zone and its components.
        */
        void open();

        /**
         * @brief Closes the AI zone and its components.
        */
        void close();

        /**
         * @brief Reports the status of the AI zone.
        */
        void reportStatus() const;

        /**
         * @brief Returns the total capacity of the AI zone.
         *
         * @return The total capacity.
        */
        int getCapacity() const;

        /**
         * @brief Handles a received technology signal.
         *
         * @param signal The received signal.
        */
        void update(const TechSignal& signal) override;
};

#endif
