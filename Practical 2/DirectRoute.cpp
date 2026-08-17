#include "DirectRoute.h"

using namespace std;

double DirectRoute::calculateDistance(double distance)
{
    return distance;
}

void DirectRoute::printMessage(Trip *context, const string &distanceUnits)
{
    double distance = calculateDistance(context->getBaseDistance());
    cout << "You took the direct route: " << distance << " " << distanceUnits;
}

string DirectRoute::getStrategyName()
{
    return "Direct";
}
