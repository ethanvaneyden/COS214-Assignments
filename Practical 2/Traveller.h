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
    void setState(TravelState *);
    TravelState *getCurrentState();
    Map *getCurrentPlace();
    void setCurrentPlace(Map *);
    void tryTransitionTo(std::string &target);
    void move();
    Traveller(TravelState *, Map *);
    virtual ~Traveller();
};

#endif