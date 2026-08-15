#ifndef SHIPSTATE_H
#define SHIPSTATE_H

#include "TravelState.h"

class ShipState : public TravelState
{
public:
    void move(Traveller *context);
    void transition(Traveller *context, Map *location);
    std::string getModeName();
    bool canTransition(std::string &target, Map *currentLocation);
};

#endif