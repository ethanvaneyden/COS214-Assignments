#ifndef AIDEMOBOOTH_H
#define AIDEMOBOOTH_H

#include "SignalSubscriber.h"
#include "EventComponent.h"
#include "TechSignal.h"

#include <iostream>

/**
 * @brief Leaf representing an AI demonstration booth.
*/
class AIDemoBooth : public EventComponent {
    private:
        bool isOpen;
        bool active;
        int capacity;
        int currentVisitors;
        bool requiresNetwork;
        bool demoRunning;

    public:
        /**
         * @brief Constructs an AI demonstration booth.
         *
         * @param capacity Maximum visitor capacity.
         * @param name Name of the booth.
        */
        explicit AIDemoBooth(int capacity, std::string name);

        /**
         * @brief Handles a received technology signal.
         *
         * @param signal The received signal.
        */
        void update(const TechSignal& signal) override;

        /**
         * @brief Opens the AI demonstration booth.
        */
        void open() override;

        /**
         * @brief Closes the AI demonstration booth.
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
         * @brief Attempts to admit visitors into the AI demonstration booth.
         *
         * Visitors are admitted only when the booth is open. The number admitted
         * cannot exceed the booth's remaining capacity. If the booth reaches
         * capacity, a FULL_CAPACITY signal is handled by the booth.
         *
         * @param visitors Number of visitors attempting to enter. Must be positive.
         * @return The number of visitors actually admitted.
        */
        int enterVisitor(int visitors);

        /**
         * @brief Removes visitors from the AI demonstration booth.
         *
         * The booth cannot remove more visitors than are currently present.
         * The visitor count therefore never becomes negative.
         *
         * @param visitors Number of visitors attempting to leave. Must be positive.
         * @return The number of visitors actually removed.
        */
        int leaveVisitor(int visitors);

        /**
         * @brief Destroys the AI demonstration booth.
        */
        ~AIDemoBooth() override = default;
};

#endif
