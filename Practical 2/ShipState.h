#ifndef SHIPSTATE_H
#define SHIPSTATE_H

#include <map>
#include <string>
#include "TravelState.h"

class ShipState : public TravelState
{
private:
    std::map<std::string, std::string> allowedTransitions = {
        {"rover", "spaceport"}};

public:
    void move(Traveller *context);
    std::string getModeName();
    bool canTransition(std::string &target, Map *currentLocation);
};

#endif