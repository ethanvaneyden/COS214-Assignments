#ifndef EXHIBITIONHALL_H
#define EXHIBITIONHALL_H

#include "SignalSubscriber.h"
#include "SignalBroadcaster.h"
#include <vector>

/**
 * @brief Represents the main exhibition hall.
 * 
 * It is a Composite that has other components (SignalSubscriber)
 * It is also the Observer (SignalSubscriber) and the Subject (SignalBroadcaster)
 * for its children
 * Onws its children but not its observers
 */
class ExhibitionHall : public SignalSubscriber, public SignalBroadcaster {
    private:
        std::vector<SignalSubscriber*> children;

    public:
        /**
         * @brief Constructs an empty exhibition hall.
        */
        ExhibitionHall();

        /**
         * @brief Adds a component to the exhibition hall.
         *
         * @param component The component to add.
        */
        void add(SignalSubscriber* component) override;

        /**
         * @brief Removes a component from the exhibition hall.
         *
         * @param component The component to remove.
        */
        void remove(SignalSubscriber* component) override;

        /**
         * @brief Opens the exhibition hall and its components.
        */
        void open();

        /**
         * @brief Closes the exhibition hall and its components.
        */
        void close();

        /**
         * @brief Reports the status of the exhibition hall.
        */
        void reportStatus() const;

        /**
         * @brief Returns the total capacity of the exhibition hall.
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

        /**
         * @brief Destroys the exhibition hall and its components.
        */
        ~ExhibitionHall() override;
};

#endif
