#ifndef DESERTFACTORY_H
#define DESERTFACTORY_H

#include "BiomeFactory.h"

#include "DesertNPC.h"
#include "DesertTreasure.h"
#include "DesertHazard.h"
#include "DesertLandmark.h"

class DesertFactory : public BiomeFactory{
    public:
        Biome* createBiome() override;
        
        NPC* createNPC() override;
        Treasure* createTreasure() override;
        Hazard* createHazard() override;
        Landmark* createLandmark() override;
};

#endif