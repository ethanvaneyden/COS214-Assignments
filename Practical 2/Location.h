#ifndef LOCATION_H
#define LOCATION_H

#include "Map.h"
#include <iostream>

class Location : public Map {
    private:
        int population;

    public:
        // takes name and optional population
        Location(const std::string& name, int pop = 0);
        
        // Prints the location details
        // Format: "Location: Mars (Population: 10000)\n"
        void describe() const override;
        
        int getPopulation() const override;
        void growPopulation(int amount) override;
        void decreasePopulation(int amount) override;

        //nothing to clean up (no heap memory)
        ~Location() override;
};

#endif