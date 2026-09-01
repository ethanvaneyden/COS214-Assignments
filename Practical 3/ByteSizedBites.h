#ifndef BYTESIZEDBIES_H
#define BYTESIZEDBIES_H

#include "SignalSubscriber.h"
#include "EventComponent.h"
#include "EventLeaf.h"
#include "TechSignal.h"

#include <iostream>
#include <unordered_map>
#include <string>

/**
 * @class ByteSizedBites
 * @brief Represents the ByteSizedBites food and refreshment facility.
 *
 * ByteSizedBites is an event leaf that manages a food and drink
 * facility within the event hierarchy. It keeps track of the
 * facility's operating status, seating capacity, available stock,
 * staff, orders, and daily special.
 *
 * The class also responds to technology-related signals through
 * the EventLeaf observer interface.
*/
class ByteSizedBites : public EventLeaf{
    private:
        /** @brief Indicates whether the facility is currently open.*/
        bool isOpen;

        // Seating

        /** @brief Total number of chairs available in the facility.*/
        int TotalChairs;

        /** @brief Number of visitors currently occupying chairs.*/
        int visitorsOnChairs;

        // Food & drinks

        /** @brief Current stock of food items.*/
        int foodStock;

        /** @brief Current stock of drinks.*/
        int drinkStock;

        /** @brief Current stock of snacks.*/
        int snackStock;

        /** @brief Current stock of energy bars.*/
        int energyBarStock;

        // Service

        /** @brief Number of staff members currently available.*/
        int staffCount;

        /** @brief Number of customer orders currently being processed.*/
        int ordersInProgress;

        // Basic information

        /** @brief Description of the current special of the day.*/
        std::string specialOfTheDay;

    public:

        /**
         * @brief Constructs a new ByteSizedBites facility.
         *
         * @param name Name assigned to the ByteSizedBites event component.
        */
        explicit ByteSizedBites(std::string name);

        // Event functionality

        /**
         * @brief Responds to a technology signal.
         *
         * Processes technology-related events such as opening,
         * closing, resuming operations, capacity changes, and
         * operational failures.
         *
         * @param signal The technology signal received by the facility.
        */
        void update(const TechSignal& signal) override;

        /**
         * @brief Opens the ByteSizedBites facility.
        */
        void open() override;

        /**
         * @brief Closes the ByteSizedBites facility.
        */
        void close() override;

        /**
         * @brief Returns the current operating status of the facility.
         *
         * @return A string describing the current status of the facility.
        */
        std::string getStatus() const override;

        /**
         * @brief Reports the status.
        */
        void reportStatus() const override;

        /**
         * @brief Gets the current number of visitors.
         *
         * @return The current number of visitors.
        */
        int getCurrentVisitors() const override;

        /**
         * @brief Attempts to seat a visitor.
         *
         * A visitor can only be seated when the facility is open
         * and there is an available chair.
         *
         * @param visitors Number of visitors attempting to enter. Must be positive.
         * @return The number of visitors actually admitted.
        */
        int enterVisitor(int visitors) override;

        /**
         * @brief Removes a visitor from the seating area.
         *
         * @param visitors Number of visitors attempting to leave. Must be positive.
         * @return The number of visitors actually removed.
        */
        int leaveVisitor(int visitors) override;

        /**
         * @brief Returns the seating capacity of the facility.
         *
         * @return The total number of available chairs.
        */
        int getCapacity() const override;

        // Open/closed status

        /**
         * @brief Gets the current open or closed status.
         *
         * @return true if the facility is open, otherwise false.
        */
        bool getIsOpen() const;

        /**
         * @brief Sets the open or closed status of the facility.
         *
         * @param status The new operating status.
        */
        void setIsOpen(bool status);

        // Seating

        /**
         * @brief Gets the total number of chairs available.
         *
         * @return The total seating capacity.
        */
        int getTotalChairs() const;

        /**
         * @brief Sets the total number of chairs available.
         *
         * @param chairs The new total seating capacity.
        */
        void setTotalChairs(int chairs);

        /**
         * @brief Gets the number of visitors currently seated.
         *
         * @return The number of visitors occupying chairs.
        */
        int getVisitorsOnChairs() const;

        /**
         * @brief Sets the number of currently seated visitors.
         *
         * @param visitors The new number of seated visitors.
        */
        void setVisitorsOnChairs(int visitors);

        /**
         * @brief Attempts to seat a visitor.
         *
         * A visitor can only be seated when the facility is open
         * and there is an available chair.
         *
         * @return true if the visitor was successfully seated,
         *         otherwise false.
        */
        bool seatVisitor();

        /**
         * @brief Removes a visitor from the seating area.
         *
         * @return true if a visitor was successfully removed,
         *         otherwise false.
        */
        bool removeVisitor();

        // Food & drinks

        /**
         * @brief Gets the current food stock.
         *
         * @return The number of food items currently available.
        */
        int getFoodStock() const;

        /**
         * @brief Sets the current food stock.
         *
         * @param stock The new food stock amount.
        */
        void setFoodStock(int stock);

        /**
         * @brief Gets the current drink stock.
         *
         * @return The number of drinks currently available.
        */
        int getDrinkStock() const;

        /**
         * @brief Sets the current drink stock.
         *
         * @param stock The new drink stock amount.
        */
        void setDrinkStock(int stock);

        /**
         * @brief Gets the current snack stock.
         *
         * @return The number of snacks currently available.
        */
        int getSnackStock() const;

        /**
         * @brief Sets the current snack stock.
         *
         * @param stock The new snack stock amount.
        */
        void setSnackStock(int stock);

        /**
         * @brief Gets the current energy bar stock.
         *
         * @return The number of energy bars currently available.
        */
        int getEnergyBarStock() const;

        /**
         * @brief Sets the current energy bar stock.
         *
         * @param stock The new energy bar stock amount.
        */
        void setEnergyBarStock(int stock);

        // Stock management

        /**
         * @brief Uses a specified amount of food stock.
         *
         * @param amount Number of food items to use.
         * @return true if the requested amount was available and used,
         *         otherwise false.
        */
        bool useFood(int amount);

        /**
         * @brief Uses a specified amount of drink stock.
         *
         * @param amount Number of drinks to use.
         * @return true if the requested amount was available and used,
         *         otherwise false.
        */
        bool useDrink(int amount);

        /**
         * @brief Uses a specified amount of snack stock.
         *
         * @param amount Number of snacks to use.
         * @return true if the requested amount was available and used,
         *         otherwise false.
        */
        bool useSnack(int amount);

        /**
         * @brief Uses a specified amount of energy bar stock.
         *
         * @param amount Number of energy bars to use.
         * @return true if the requested amount was available and used,
         *         otherwise false.
        */
        bool useEnergyBar(int amount);

        // Service

        /**
         * @brief Gets the number of staff members.
         *
         * @return The current number of staff members.
        */
        int getStaffCount() const;

        /**
         * @brief Sets the number of staff members.
         *
         * @param count The new number of staff members.
        */
        void setStaffCount(int count);

        /**
         * @brief Gets the number of orders currently in progress.
         *
         * @return The number of active orders.
        */
        int getOrdersInProgress() const;

        /**
         * @brief Sets the number of orders currently in progress.
         *
         * @param orders The new number of active orders.
        */
        void setOrdersInProgress(int orders);

        /**
         * @brief Starts processing a new customer order.
         *
         * A new order can only be started when the facility is open
         * and staff members are available.
        */
        void startOrder();

        /**
         * @brief Completes an order currently in progress.
         *
         * If there are active orders, one order is removed from
         * the number of orders in progress.
        */
        void completeOrder();

        // Basic information

        /**
         * @brief Gets the current special of the day.
         *
         * @return The description of the special of the day.
        */
        std::string getSpecialOfTheDay() const;

        /**
         * @brief Sets the special of the day.
         *
         * @param special Description of the new special of the day.
        */
        void setSpecialOfTheDay(const std::string& special);

        /**
         * @brief Destroys the ByteSizedBites facility.
        */
        ~ByteSizedBites() override = default;
};

#endif
