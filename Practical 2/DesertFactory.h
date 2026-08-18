#ifndef DESERTFACTORY_H
#define DESERTFACTORY_H

#include "BiomeFactory.h"

class DesertFactory : public BiomeFactory{
    public:
        NPC* createNPC() override;
        Treasure* createTreasure() override;
        Hazard* createHazard() override;
        Landmark* createLandmark() override;
};

#endif