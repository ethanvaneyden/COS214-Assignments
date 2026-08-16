#ifndef TRAVELSTATE_H
#define TRAVELSTATE_H

#include <string>
#include <iostream>
#include "Traveller.h"
class Map;

class TravelState
{
public:
    virtual void move(Traveller *context) = 0;
    virtual void transition(Traveller *context, std::string &target) = 0;
    virtual std::string getModeName() = 0;
    virtual bool canTransition(std::string &target, Map *currentLocation) = 0;
};

#endif