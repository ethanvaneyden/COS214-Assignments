#include "ForestFactory.h"

Biome* ForestFactory::createBiome(){
    return new Biome(createNPC(), createTreasure(), createHazard(), createLandmark());
}

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