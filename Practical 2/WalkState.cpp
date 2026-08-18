#include "WalkState.h"
#include "Traveller.h"
#include "Map.h"
#include "Biome.h"

using namespace std;

/*
Handles the move from planet to planet
*/
void WalkState::move(Traveller *context)
{
    if (context == nullptr)
    {
        cout << "Failed to move\n";
        return;
    }

    Map *currentLocation = context->getCurrentPlace();
    if (currentLocation == nullptr)
    {
        cout << "No current location\n";
        return;
    }

    cout << "You're exploring on foot. Get inside a rover to move to different locations.\n";
}

/*
Checks if a the player can transition state
Command must be "rover" and the planet must have the spaceport decorator
*/
bool WalkState::canTransition(std::string &target, Map *currentLocation)
{
    if (currentLocation == nullptr)
    {
        return false;
    }

    auto neededDecoration = allowedTransitions.find(target);
    if (neededDecoration == allowedTransitions.end())
    {
        return false;
    }
    if (neededDecoration->second == "anything")
    {
        return true;
    }
    else
    {
        return currentLocation->hasDecorator(neededDecoration->second);
    }
}

string WalkState::getModeName()
{
    return "Walk";
}

void WalkState::displayMenu()
{
    cout << "=== Exploring on foot ===\n"
         << "Type the command you want to do\n"
         << "1. speak - Speak to an NPC\n"
         << "2. treasure - Hunt for treasure\n"
         << "3. hazard - Explore this biomes hazard\n"
         << "4. landmark - Explore this biome's landmark"
         << "5. rover - Board the rover\n";
}

void WalkState::handleInput(string &input, Traveller *context)
{
    if (context == nullptr)
    {
        cout << "No traveller context available\n";
        return;
    }

    Map *currentLocation = context->getCurrentPlace();
    if (currentLocation == nullptr)
    {
        cout << "No current location available\n";
        return;
    }

    if (input.empty())
    {
        cout << "No command entered\n";
        return;
    }

    Biome *currentBiome = currentLocation->getCurrentBiome();
    if (currentBiome == nullptr)
    {
        cout << "No biome data available for this location\n";
        return;
    }

    if (input == "speak")
    {
        currentBiome->speakToNPC();
    }
    else if (input == "treasure")
    {
        currentBiome->huntTreasure();
    }
    else if (input == "hazard")
    {
        currentBiome->exploreHazard();
    }
    else if (input == "landmark")
    {
        currentBiome->exploreLandmark();
    }
    else
    {
        cout << "Invalid command\n";
    }
}