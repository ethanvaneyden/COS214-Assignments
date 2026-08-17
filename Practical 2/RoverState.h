#ifndef ROVERSTATE_H
#define ROVERSTATE_H

#include "TravelState.h"
#include <map>
#include <string>

class RoverState : public TravelState
{
private:
    std::map<Trans, std::string> allowedTransitions = {
        {"ship", "spaceport"},
        {"walk", "anything"}};

public:
    void move(Traveller *context);
    std::string getModeName();
    bool canTransition(std::string &target, Map *currentLocation);
};

#endif