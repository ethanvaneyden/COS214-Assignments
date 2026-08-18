#include "Traveller.h"
#include "TravelState.h"
#include <iostream>

using namespace std;

bool Traveller::setState(TravelState *state, const std::string &targetMode)
{
    if (state == nullptr || currentState == nullptr)
    {
        currentState = state;
        return true;
    }

    // Check if transition is valid using the current state's canTransition method
    std::string target = targetMode;
    if (!currentState->canTransition(target, currentPlanet))
    {
        return false; // Transition not allowed
    }

    currentState = state;
    return true;
}

TravelState *Traveller::getCurrentState()
{
    return currentState;
}

Map *Traveller::getCurrentPlace()
{
    return currentLocation;
}

void Traveller::setCurrentPlace(Map *place)
{
    currentLocation = place;
}

Map *Traveller::getCurrentPlanet()
{
    return currentPlanet;
}

void Traveller::setCurrentPlanet(Map *planet)
{
    currentPlanet = planet;
}

Traveller::Traveller(TravelState *state, Map *map, Map *planet)
    : currentState(state), currentLocation(map), currentPlanet(planet)
{
}