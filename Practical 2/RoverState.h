#ifndef ROVERSTATE_H
#define ROVERSTATE_H

#include "TravelState.h"

class RoverState : public TravelState
{
public:
    void move(Traveller *context);
    void transition(Traveller *context, Map *location);
    std::string getModeName();
};

#endif