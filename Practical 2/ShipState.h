#ifndef SHIPSTATE_H
#define SHIPSTATE_H
#include <map>
#include "TravelState.h"

class ShipState : public TravelState
{
private:
    std::map<std::string, std::string> allowedTransitions = {
        {"rover", "spaceport"}};

public:
    void move(Traveller *context);
    void transition(Traveller *context, std::string &target);
    std::string getModeName();
};

#endif