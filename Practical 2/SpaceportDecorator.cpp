#include "SpaceportDecorator.h"
#include <iostream>

SpaceportDecorator::SpaceportDecorator(Map* place)
    : MapDecorator(place)
{}

void SpaceportDecorator::describe() const{
    std::cout << "[Spaceport] ";
    MapDecorator::describe();
}

bool SpaceportDecorator::hasDecorator(const std::string& name) const{
    if(name == "spaceport")
        return true;
    return MapDecorator::hasDecorator(name);
}

SpaceportDecorator::~SpaceportDecorator(){
}