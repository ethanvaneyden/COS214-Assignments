#ifndef ROUTESTRATEGY_H
#define ROUTESTRATEGY_H
#include "Trip.h"

class RouteStrategy
{

public:
    double calculateDistance(double distance);
    void printMessage(Trip *context, const std::string distanceUnits);
    std::string getStrategyName();
};

#endif
