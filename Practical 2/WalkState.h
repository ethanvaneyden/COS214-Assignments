#ifndef WALKSTATE_H
#define WALKSTATE_H

#include "TravelState.h"
#include <map>
#include <string>

class WalkState : public TravelState
{
    std::map<std::string, std::string> allowedTransitions = {
        {"ship", "spaceport"},
        {"rover", "anything"}};

public:
    void move(Traveller *context);
    std::string getModeName();
    bool canTransition(std::string &target, Map *currentLocation);
    void displayMenu();
    void handleInput(std::string &input, Traveller *context);
    std::string getDistanceUnit();
};

#endif