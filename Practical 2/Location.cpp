#include "Location.h"

Location::Location(const std::string& name, int pop = 0) : Map(name), population(pop) {
}

void Location::describe() const{
    std::cout << "Location: " << getName() << " (Population: " << getPopulation() << ")\n";
}

int Location::getPopulation() const{
    return this->population;
}

void Location::growPopulation(int amount){
    this->population += amount;
    std::cout << "Population grew by " << amount << std::endl;

    describe();
}

void Location::decreasePopulation(int amount){
    if(this->population <= 0){
        std::cout << "There are no inhabitants to decrease\n";
        describe();
        return;
    }

    this->population -= amount;
    if(this->population < 0) 
        this->population = 0;

    std::cout << "Population decreased by " << amount << std::endl;
    describe();
}

Location::~Location(){
    //nothing to clean up (no heap memory)
}