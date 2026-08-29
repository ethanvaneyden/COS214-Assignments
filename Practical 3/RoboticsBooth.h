#ifndef ROBOTICSBOOTH_H
#define ROBOTICSBOOTH_H

#include "SignalSubscriber.h"
#include "EventComponent.h"
#include "TechSignal.h"

#include <iostream>

/**
 * @brief Leaf representing a robotics demonstration booth.
*/
class RoboticsBooth : public EventComponent {
    private:
        bool isOpen;
        bool active;
        bool safeMode;
        int capacity;
        int currentVisitors;
        bool robotsActive;
        bool requiresPower;

    public:
        /**
         * @brief Constructs a robotics demonstration booth.
         *
         * @param capacity Maximum visitor capacity.
         * @param name Name of the booth.
        */
        explicit RoboticsBooth(int capacity, std::string name);

        /**
         * @brief Handles a received technology signal.
         *
         * @param signal The received signal.
        */
        void update(const TechSignal& signal) override;

        /**
         * @brief Opens the robotics demonstration booth.
        */
        void open() override;

        /**
         * @brief Closes the robotics demonstration booth.
        */
        void close() override;

        /**
         * @brief Reports the booth status.
        */
        void reportStatus() const override;

        /**
         * @brief Returns the booth capacity.
         *
         * @return Maximum visitor capacity.
        */
        int getCapacity() const override;

        /**
         * @brief Destroys the robotics demonstration booth.
        */
        ~RoboticsBooth() override = default;
};

#endif
