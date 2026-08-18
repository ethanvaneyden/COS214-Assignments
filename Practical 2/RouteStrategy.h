#ifndef ROUTESTRATEGY_H
#define ROUTESTRATEGY_H

#include <string>

class Trip;

class RouteStrategy{
    public:
        virtual double calculateDistance(double distance) = 0;
        virtual void printMessage(Trip *context, const std::string &distanceUnits) = 0;
        virtual std::string getStrategyName() = 0;

        virtual ~RouteStrategy() {}
};

#endif