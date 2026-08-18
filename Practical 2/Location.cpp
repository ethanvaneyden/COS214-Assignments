#include "Location.h"
#include "Biome.h"

Location::Location(const std::string& name, int pop, double distance, Biome* biome)
    : Map(name, distance), population(pop), biome(biome)
{}

void Location::describe() const{
    std::cout << "Location: " << getName() << " (Population: " << getPopulation() << ")\n";
}

int Location::getPopulation() const{
    return this->population;
}

void Location::growPopulation(int amount){
    if(amount < 0){
        std::cout << "Invalid amount. Population growth cannot be negative.\n";
        return;
    }

    this->population += amount;

    // taking care of negative amount (e.g. -500)
    if(this->population < 0) 
        this->population = 0;

    std::cout << "Location: Population grew by " << amount << std::endl;

    describe();
}

void Location::decreasePopulation(int amount){
    if(amount < 0){
        std::cout << "Invalid amount. Population decrease cannot be negative.\n";
        return;
    }

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

Biome* Location::getBiome() const{
    return this->biome;
}

void Location::setBiome(Biome* biome){
    this->biome = biome;
}

Biome* Location::getCurrentBiome(){
    return this->biome;
}

Location::~Location(){
    if(biome != nullptr)
        delete biome;
}