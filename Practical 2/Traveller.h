#ifndef TRAVELLER_H
#define TRAVELLER_H

#include <string>

class TravelState;
class Map;
class Trip;

class Traveller
{
private:
    TravelState *currentState;
    Map *currentLocation;

public:
    void setState(TravelState *state);
    TravelState *getCurrentState();
    Map *getCurrentPlace();
    void setCurrentPlace(Map *map);
    Traveller(TravelState *state, Map *map);
};

#endif