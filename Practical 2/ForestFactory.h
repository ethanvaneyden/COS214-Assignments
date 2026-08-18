#ifndef FORESTFACTORY_H
#define FORESTFACTORY_H

#include "BiomeFactory.h"

#include "ForestNPC.h"
#include "ForestTreasure.h"
#include "ForestHazard.h"
#include "ForestLandmark.h"

class ForestFactory : public BiomeFactory{
    public:
        Biome* createBiome() override;
        
        NPC* createNPC() override;
        Treasure* createTreasure() override;
        Hazard* createHazard() override;
        Landmark* createLandmark() override;
};

#endif