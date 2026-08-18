#include "HazardDecorator.h"

HazardDecorator::HazardDecorator(Map* place)
    : MapDecorator(place)
{}

void HazardDecorator::describe() const{
    std::cout << "[Hazardous Area] ";
    MapDecorator::describe();
}

bool HazardDecorator::hasDecorator(const std::string& name) const{
    if (name == "hazard")
        return true;
    return MapDecorator::hasDecorator(name);
}

HazardDecorator::~HazardDecorator(){
}