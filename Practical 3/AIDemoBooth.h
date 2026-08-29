#ifndef AIDEMOBOOTH_H
#define AIDEMOBOOTH_H

#include "SignalSubscriber.h"

/**
 * @brief Leaf representing an AI demonstration booth.
*/
class AIDemoBooth : public SignalSubscriber {
    private:
        bool openState;
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
        */
        explicit AIDemoBooth(int capacity);

        /**
         * @brief Handles a received technology signal.
         *
         * @param signal The received signal.
        */
        void update(const TechSignal& signal) override;

        /**
         * @brief Opens the AI demonstration booth.
        */
        void open();

        /**
         * @brief Closes the AI demonstration booth.
        */
        void close();

        /**
         * @brief Reports the booth status.
        */
        void reportStatus() const;

        /**
         * @brief Returns the booth capacity.
         *
         * @return Maximum visitor capacity.
        */
        int getCapacity() const;

        /**
         * @brief Destroys the AI demonstration booth.
        */
        ~AIDemoBooth() override = default;
};

#endif
