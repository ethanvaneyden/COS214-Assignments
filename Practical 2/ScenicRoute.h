#ifndef SCENICROUTE_H
#define SCENICROUTE_H

#include "RouteStrategy.h"

class ScenicRoute : public RouteStrategy
{
    double calculateDistance(double distance);
    void printMessage(Trip *context, const std::string &distanceUnits);
    std::string getStrategyName();
};

#endif