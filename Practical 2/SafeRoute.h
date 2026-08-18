#ifndef SAFEROUTE_H
#define SAFEROUTE_H

#include "RouteStrategy.h"
#include <iostream>

class Trip;

class SafeRoute : public RouteStrategy
{
    double calculateDistance(double distance);
    void printMessage(Trip *context, const std::string &distanceUnits);
    std::string getStrategyName();
};

#endif