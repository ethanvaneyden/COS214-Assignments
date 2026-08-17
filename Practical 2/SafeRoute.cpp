#include "SafeRoute.h"

using namespace std;

double SafeRoute::calculateDistance(double distance)
{
    return 1.2 * distance;
}

void SafeRoute::printMessage(Trip *context, const string &distanceUnits)
{
    double distance = calculateDistance(context->getBaseDistance());
    cout << "You took the safe route: " << distance << " " << distanceUnits;
}
