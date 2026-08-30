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
         * @brief Attempts to admit visitors into the robotics demonstration booth.
         *
         * Visitors are admitted only when the booth is open. The number admitted
         * cannot exceed the booth's remaining capacity. If the booth reaches
         * capacity, a FULL_CAPACITY signal is handled by the booth.
         *
         * @param visitors Number of visitors attempting to enter. Must be positive.
         * @return The number of visitors actually admitted.
        */
        int RoboticsBooth::enterVisitor(int visitors);

        /**
         * @brief Removes visitors from the robotics demonstration booth.
         *
         * The booth cannot remove more visitors than are currently present.
         * The visitor count therefore never becomes negative.
         *
         * @param visitors Number of visitors attempting to leave. Must be positive.
         * @return The number of visitors actually removed.
        */
        int leaveVisitor(int visitors);

        /**
         * @brief Destroys the robotics demonstration booth.
        */
        ~RoboticsBooth() override = default;
};

#endif
