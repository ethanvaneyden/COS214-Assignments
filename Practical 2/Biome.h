#ifndef BIOME_H
#define BIOME_H

#include "NPC.h"
#include "Treasure.h"
#include "Harzard.h"
#include "Landmark.h"

class Biome{
    private:
        NPC* npc;
        Treasure* treasure;
        Hazard* hazard;
        Landmark* landmark;

    public:
        Biome(NPC* npc, Treasure* treasure, Hazard* hazard, Landmark* landmark);

        void speakToNPC();
        void huntTreasure();
        void exploreHazard();
        void exploreLandmark();

        ~Biome();
};

#endif