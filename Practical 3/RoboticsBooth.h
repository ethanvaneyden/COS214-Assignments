#ifndef ROBOTICSBOOTH_H
#define ROBOTICSBOOTH_H

#include "SignalSubscriber.h"

/**
 * @brief Leaf representing a robotics demonstration booth.
*/
class RoboticsBooth : public SignalSubscriber {
    private:
        bool openState;
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
        */
        explicit RoboticsBooth(int capacity);

        /**
         * @brief Handles a received technology signal.
         *
         * @param signal The received signal.
        */
        void update(const TechSignal& signal) override;

        /**
         * @brief Opens the robotics demonstration booth.
        */
        void open();

        /**
         * @brief Closes the robotics demonstration booth.
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
         * @brief Destroys the robotics demonstration booth.
        */
        ~RoboticsBooth() override = default;
};

#endif
