#include "ScenicRoute.h"

using namespace std;

double ScenicRoute::calculateDistance(double distance)
{
    return 1.5 * distance;
}

void ScenicRoute::printMessage(Trip *context, const string &distanceUnits)
{
    double distance = calculateDistance(context->getBaseDistance());
    cout << "You took the scenic route: " << distance << " " << distanceUnits;
}
