#ifndef TRAVELSTATE_H
#define TRAVELSTATE_H

#include <string>
#include <iostream>

class Traveller;
class Map;

class TravelState
{
public:
    virtual void move(Traveller *context) = 0;
    virtual std::string getModeName() = 0;
    virtual bool canTransition(std::string &target, Map *currentLocation) = 0;
    virtual void displayMenu() = 0;
    virtual void handleInput(std::string &input, Traveller *context) = 0;
    virtual std::string getDistanceUnit() = 0;
    virtual ~TravelState() = default;
};

#endif