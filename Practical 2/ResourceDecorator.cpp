#include "ResourceDecorator.h"

ResourceDecorator::ResourceDecorator(Map* place)
    : MapDecorator(place)
{}

void ResourceDecorator::describe() const{
    std::cout << "[Resource-Rich] ";
    MapDecorator::describe();
}

bool ResourceDecorator::hasDecorator(const std::string& name) const{
    if (name == "resource")
        return true;
    return MapDecorator::hasDecorator(name);
}

ResourceDecorator::~ResourceDecorator(){
}