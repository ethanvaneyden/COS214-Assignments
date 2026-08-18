#ifndef DIRECTROUTE_H
#define DIRECTROUTE_H

#include "RouteStrategy.h"
#include <iostream>

class Trip;

class DirectRoute : public RouteStrategy
{
    double calculateDistance(double distance);
    void printMessage(Trip *context, const std::string &distanceUnits);
    std::string getStrategyName();
};

#endif