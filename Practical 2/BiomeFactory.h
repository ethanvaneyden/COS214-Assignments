#ifndef BIOMEFACTORY_H
#define BIOMEFACTORY_H

#include "Biome.h"

#include "NPC.h"
#include "Treasure.h"
#include "Harzard.h"
#include "Landmark.h"

class BiomeFactory{
    public:
        virtual Biome* createBiome() = 0;

        virtual NPC* createNPC() = 0;
        virtual Treasure* createTreasure() = 0;
        virtual Hazard* createHazard() = 0;
        virtual Landmark* createLandmark() = 0;

        virtual ~BiomeFactory() = default;
};

#endif