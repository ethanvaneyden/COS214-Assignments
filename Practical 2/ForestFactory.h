#ifndef FORESTFACTORY_H
#define FORESTFACTORY_H

#include "BiomeFactory.h"

class ForestFactory : public BiomeFactory{
    public:
        NPC* createNPC() override;
        Treasure* createTreasure() override;
        Hazard* createHazard() override;
        Landmark* createLandmark() override;
};

#endif