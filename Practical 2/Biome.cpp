#include "Biome.h"

Biome::Biome(NPC* npc, Treasure* treasure, Hazard* hazard, Landmark* landmark)
    : npc(npc), treasure(treasure), hazard(hazard), landmark(landmark)
{}

void Biome::speakToNPC(){
    if(npc != nullptr)
        npc->speak();
}

void Biome::huntTreasure(){
    if(treasure != nullptr)
        treasure->treasureHunt();
}

void Biome::exploreHazard(){
    if(hazard != nullptr)
        hazard->exploreHazard();
}

void Biome::exploreLandmark(){
    if(landmark != nullptr)
        landmark->exploreLandmark();
}

Biome::~Biome(){
    //checking null, just to be safe
    if(npc != nullptr)
        delete npc;

    if(treasure != nullptr)
        delete treasure;

    if(hazard != nullptr)
        delete hazard;

    if(landmark != nullptr)
        delete landmark;
}