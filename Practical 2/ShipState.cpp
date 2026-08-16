#include "ShipState.h"
using namespace std;

void ShipState::move(Traveller *context)
{
    if (context == nullptr)
    {
        cout << "Failed to move\n";
        return;
    }
    Map *newLocation = currentLocation->nextPlanet();
    context->setCurrentPlace(newLocation);
    cout << "You travelled to " << newLocation->getName() << endl;
}

void ShipState::transition(Traveller *context, string &target)
{
    if (context == nullptr)
    {
        cout << "Failed to transition";
        return;
    }
    if (allowedTransitions.find(target) == allowedTransitions.end())
    {
        cout << "You are not allowed to do this!\n";
        return;
    }
    auto neededDecoration = allowedTransitions.find(target);
    if (!context->getCurrentPlace()->hasDecorator((neededDecoration->second)))
    {
        cout << "Your planet needs a spaceport!\n";
        return;
    }
    context->setState(new RoverState());
}

string ShipState::getModeName()
{
    return "Ship";
}
