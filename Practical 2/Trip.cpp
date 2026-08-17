#include "Trip.h"

void Trip::setStrategy(RouteStrategy *strategy)
{
    this->strategy = strategy;
}
RouteStrategy *Trip::getStrategy()
{
    return strategy;
}
void Trip::setBaseDistance(int distance)
{
    baseDistance = distance;
}
double Trip::getBaseDistance()
{
    return baseDistance;
}

Trip::Trip(RouteStrategy *strategy, double baseDistance) : strategy(strategy), baseDistance(baseDistance)
{
}