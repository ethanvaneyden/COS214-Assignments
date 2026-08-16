#include "ShipState.h"
#include "RoverState.h"

using namespace std;

/*
Handles the move from planet to planet
*/
void ShipState::move(Traveller *context)
{
    if (context == nullptr)
    {
        cout << "Failed to move\n";
        return;
    }

    Map *currentLocation = context->getCurrentPlace();
    if (currentLocation == nullptr)
    {
        cout << "No current location\n";
        return;
    }

    Map *newLocation = currentLocation->nextPlanet();
    if (newLocation == nullptr)
    {
        cout << "No next planet available\n";
        return;
    }

    context->setCurrentPlace(newLocation);
    cout << "You travelled to " << newLocation->getName() << endl;
}
/*
Handles the transition to rover state
*/
void ShipState::transition(Traveller *context, Map *location)
{
    if (context == nullptr || location == nullptr)
    {
        cout << "Failed to transition\n";
        return;
    }

    std::string target = "rover";
    if (!canTransition(target, location))
    {
        cout << "You are not allowed to do this!\n";
        return;
    }

    context->setState(new RoverState());
    cout << "You transitioned to RoverState\n";
}

/*
Checks if a the player can transition state
Command must be ship and the planet must have the spaceport decorator
*/
bool ShipState::canTransition(std::string &target, Map *currentLocation)
{
    if (currentLocation == nullptr)
    {
        return false;
    }

    auto neededDecoration = allowedTransitions.find(target);
    if (neededDecoration == allowedTransitions.end())
    {
        return false;
    }

    return currentLocation->hasDecorator(neededDecoration->second);
}

string ShipState::getModeName()
{
    return "Ship";
}
