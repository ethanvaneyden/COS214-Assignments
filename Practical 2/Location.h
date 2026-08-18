#ifndef LOCATION_H
#define LOCATION_H

#include "Map.h"
#include <iostream>

class Biome;

class Location : public Map {
    private:
        int population;
        Biome* biome;

    public:
        // takes name and optional population
        Location(const std::string& name, int pop = 0, double distance = 0.0, Biome* biome = nullptr);
        
        // Prints the location details
        // Format: "Location: Mars (Population: 10000)\n"
        void describe() const override;
        
        int getPopulation() const override;
        void growPopulation(int amount) override;
        void decreasePopulation(int amount) override;

        Biome* getBiome() const;
        void setBiome(Biome* biome);

        //nothing to clean up (no heap memory)
        ~Location() override;
};

#endif