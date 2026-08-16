#ifndef ROVERSTATE_H
#define ROVERSTATE_H

#include "TravelState.h"

class RoverState : public TravelState
{
public:
    void move(Traveller *context);
    std::string getModeName();
    bool canTransition(std::string &target, Map *currentLocation);
};

#endif