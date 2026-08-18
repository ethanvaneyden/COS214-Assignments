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
    Map *currentPlanet;

public:
    bool setState(TravelState *state, const std::string &targetMode);
    TravelState *getCurrentState();
    Map *getCurrentPlace();
    void setCurrentPlace(Map *map);
    Map *getCurrentPlanet();
    void setCurrentPlanet(Map *planet);
    Traveller(TravelState *state, Map *map, Map *planet);
};

#endif