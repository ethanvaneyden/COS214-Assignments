#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <iostream>

class RouteStrategy;

class Trip
{
private:
    RouteStrategy *strategy;
    double baseDistance;

public:
    void setStrategy(RouteStrategy *);
    RouteStrategy *getStrategy();
    void setBaseDistance(int distance);
    double getBaseDistance();
    Trip(RouteStrategy *strategy, double baseDistance);
};

#endif