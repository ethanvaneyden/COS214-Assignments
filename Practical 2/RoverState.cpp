#include "RoverState.h"

using namespace std;

/*
Handles the move from location to location
*/
void RoverState::move(Traveller *context)
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

    Map *newLocation = currentLocation->nextLocation();
    if (newLocation == nullptr)
    {
        cout << "No next location available\n";
        return;
    }

    context->setCurrentPlace(newLocation);
    cout << "You travelled to " << newLocation->getName() << endl;
}

/*
Checks if a the player can transition state
Command must be ship and the location must have a spaceport
Command must be walk and the location needs no specific decorator
*/
bool RoverState::canTransition(std::string &target, Map *currentLocation)
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
    if (neededDecoration->second == "anything")
    {
        return true;
    }
    else
    {
        return currentLocation->hasDecorator(neededDecoration->second);
    }
}

string RoverState::getModeName()
{
    return "Rover";
}

void RoverState::displayMenu()
{
    cout << "=== Inside rover ===\n"
         << "Type the command you want to do\n"
         << "1. move - Move to next location on the planet\n"
         << "2. walk - Disembark rover and explore the location on foot\n";
}

void RoverState::handleInput(string &input, Traveller *context)
{
    if (context == nullptr)
    {
        cout << "No traveller context available\n";
        return;
    }

    if (input.empty())
    {
        cout << "No command entered\n";
        return;
    }

    if (input == "move")
    {
        move(context);
    }
    else
    {
        cout << "Invalid command\n";
    }
}
