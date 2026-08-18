#include "DesertFactory.h"

NPC* DesertFactory::createNPC(){
    return new DesertNPC();
}

Treasure* DesertFactory::createTreasure(){
    return new DesertTreasure();
}

Hazard* DesertFactory::createHazard(){
    return new DesertHazard();
}

Landmark* DesertFactory::createLandmark(){
    return new DesertLandmark();
}