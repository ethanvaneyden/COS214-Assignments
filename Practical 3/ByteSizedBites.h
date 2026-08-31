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
    explicit ByteSizedBites();

    void update(const TechSignal& signal) override;

    void open() override;
    void close() override;

    std::string getStatus() const override;

    int getCapacity() const override;

    ~ByteSizedBites() override = default;
};

#endif