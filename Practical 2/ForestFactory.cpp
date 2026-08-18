#include "ForestFactory.h"

NPC* ForestFactory::createNPC(){
    return new ForestNPC();
}

Treasure* ForestFactory::createTreasure(){
    return new ForestTreasure();
}

Hazard* ForestFactory::createHazard(){
    return new ForestHazard();
}

Landmark* ForestFactory::createLandmark(){
    return new ForestLandmark();
}