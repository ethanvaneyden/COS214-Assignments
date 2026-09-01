#ifndef BYTESIZEDBITES_H
#define BYTESIZEDBITES_H

#include "EventLeaf.h"
#include "TechSignal.h"
#include <iostream>
#include <string>

class ByteSizedBites : public EventLeaf {
private:
    bool isOpen;
    int TotalChairs;
    int visitorsOnChairs;
    int foodStock;
    int drinkStock;
    int snackStock;
    int energyBarStock;
    int staffCount;
    int ordersInProgress;
    std::string specialOfTheDay;
    std::string lastMessage;

public:
    explicit ByteSizedBites(EventComponent *parent = nullptr);
    ~ByteSizedBites() override = default;

    void update(const TechSignal &signal) override;
    void open() override;
    void close() override;

    std::string getStatus() const override;

    int getCapacity() const override;
    int getCurrentVisitors() const override;
    int enterVisitor(int visitors) override;
    int leaveVisitor(int visitors) override;

    bool getIsOpen() const;
    void setIsOpen(bool status);
    int getTotalChairs() const;
    void setTotalChairs(int chairs);
    int getVisitorsOnChairs() const;
    void setVisitorsOnChairs(int visitors);
    bool seatVisitor();
    bool removeVisitor();

    int getFoodStock() const;
    void setFoodStock(int stock);
    int getDrinkStock() const;
    void setDrinkStock(int stock);
    int getSnackStock() const;
    void setSnackStock(int stock);
    int getEnergyBarStock() const;
    void setEnergyBarStock(int stock);

    bool useFood(int amount);
    bool useDrink(int amount);
    bool useSnack(int amount);
    bool useEnergyBar(int amount);

    int getStaffCount() const;
    void setStaffCount(int count);
    int getOrdersInProgress() const;
    void setOrdersInProgress(int orders);
    void startOrder();
    void completeOrder();

    std::string getSpecialOfTheDay() const;
    void setSpecialOfTheDay(const std::string &special);
};

#endif // BYTESIZEDBITES_H