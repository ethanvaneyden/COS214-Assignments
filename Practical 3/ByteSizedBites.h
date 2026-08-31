#ifndef BYTESIZEDBIES_H
#define BYTESIZEDBIES_H

#include "SignalSubscriber.h"
#include "EventComponent.h"
#include "EventLeaf.h"
#include "TechSignal.h"

#include <iostream>
#include <unordered_map>
#include <string>

class ByteSizedBites : public EventLeaf {
    private:
        bool isOpen;

        // Seating
        int TotalChairs;
        int visitorsOnChairs;

        // Food & drinks
        int foodStock;
        int drinkStock;
        int snackStock;
        int energyBarStock;

        // Service
        int staffCount;
        int ordersInProgress;

        // Basic information
        std::string specialOfTheDay;

    public:
        explicit ByteSizedBites(std::string name);

        // Event functionality
        void update(const TechSignal& signal) override;

        void open() override;
        void close() override;

        std::string getStatus() const override;
        int getCapacity() const override;

        // Open/closed status
        bool getIsOpen() const;
        void setIsOpen(bool status);

        // Seating
        int getTotalChairs() const;
        void setTotalChairs(int chairs);

        int getVisitorsOnChairs() const;
        void setVisitorsOnChairs(int visitors);

        bool seatVisitor();
        bool removeVisitor();

        // Food & drinks
        int getFoodStock() const;
        void setFoodStock(int stock);

        int getDrinkStock() const;
        void setDrinkStock(int stock);

        int getSnackStock() const;
        void setSnackStock(int stock);

        int getEnergyBarStock() const;
        void setEnergyBarStock(int stock);

        // Stock management
        bool useFood(int amount);
        bool useDrink(int amount);
        bool useSnack(int amount);
        bool useEnergyBar(int amount);

        // Service
        int getStaffCount() const;
        void setStaffCount(int count);

        int getOrdersInProgress() const;
        void setOrdersInProgress(int orders);

        void startOrder();
        void completeOrder();

        // Basic information
        std::string getSpecialOfTheDay() const;
        void setSpecialOfTheDay(const std::string& special);

        ~ByteSizedBites() override = default;
};

#endif
