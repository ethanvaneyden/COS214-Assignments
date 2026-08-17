#include "MapDecorator.h"

MapDecorator::MapDecorator(Map* place)
    : Map(place->getName(), place->getDistance()), wrapped(place)
{}

std::string MapDecorator::getName() const{
    return this->wrapped->getName();
}

void MapDecorator::describe() const{
    this->wrapped->describe();
}

int MapDecorator::getPopulation() const{
    return this->wrapped->getPopulation();
}

void MapDecorator::growPopulation(int amount){
    this->wrapped->growPopulation(amount);
}

void MapDecorator::decreasePopulation(int amount){
    this->wrapped->decreasePopulation(amount);
}

void MapDecorator::add(Map* child){
    this->wrapped->add(child);
}

void MapDecorator::remove(Map* child){
    this->wrapped->remove(child);
}

Map* MapDecorator::getChild(int index) const{
    return this->wrapped->getChild(index);
}

int MapDecorator::getChildCount() const{
    return this->wrapped->getChildCount();
}

double MapDecorator::getDistance() const{
    return this->wrapped->getDistance();
}

void MapDecorator::setDistance(double distance){
    this->wrapped->setDistance(distance);
}

bool MapDecorator::hasDecorator(const std::string& name) const{
    return wrapped->hasDecorator(name);
}

MapDecorator::~MapDecorator(){
    if(this->wrapped != nullptr)
        delete wrapped;
}
