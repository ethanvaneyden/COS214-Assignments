#include "Traveller.h"

void Traveller::setState(TravelState *state)
{
    currentState = state;
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

Traveller::Traveller(TravelState *state, Map *map) : currentState(state), currentLocation(map)
{
}