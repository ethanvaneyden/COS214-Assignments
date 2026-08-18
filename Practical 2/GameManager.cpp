#include "GameManager.h"
#include "Traveller.h"
#include "TravelState.h"
#include "Map.h"
#include "Location.h"
#include "BiomeFactory.h"
#include "Trip.h"

GameManager::GameManager()
    : traveller(nullptr), world(nullptr), trip(nullptr)
{
}

GameManager::~GameManager()
{
    if (traveller != nullptr)
        delete traveller;

    if (world != nullptr)
        delete world;

    if (trip != nullptr)
        delete trip;
}

void GameManager::setWorld(Map *world)
{
    this->world = world;
}

Map *GameManager::getWorld() const
{
    return world;
}

void GameManager::setTraveller(Traveller *traveller)
{
    this->traveller = traveller;
}

Traveller *GameManager::getTraveller() const
{
    return traveller;
}

void GameManager::setTrip(Trip *trip)
{
    this->trip = trip;
}

Trip *GameManager::getTrip() const
{
    return trip;
}

void GameManager::setState(TravelState *state)
{
    if (traveller != nullptr && state != nullptr)
        traveller->setState(state, state->getModeName());
}

TravelState *GameManager::getState() const
{
    if (traveller == nullptr)
        return nullptr;

    return traveller->getCurrentState();
}

void GameManager::displayStateMenu()
{
    if (traveller == nullptr)
        return;

    TravelState *state = traveller->getCurrentState();

    if (state != nullptr)
        state->displayMenu();
}

void GameManager::handleInput(std::string input)
{
    if (traveller == nullptr)
        return;

    TravelState *state = traveller->getCurrentState();

    if (state != nullptr)
        state->handleInput(input, traveller);
}

void GameManager::assignBiome(Map *location, BiomeFactory *factory)
{
    if (location == nullptr || factory == nullptr)
        return;

    // Only assign biome to leaf nodes (Locations).
    // Composite nodes (Regions) don't store biomes; only their leaf children do.
    // To be safe and avoid memory leaks, we only create the biome if we can store it.
    Location *leaf = dynamic_cast<Location *>(location);
    if (leaf == nullptr)
        return; // Not a leaf node; cannot store biome

    leaf->setBiome(factory->createBiome());
}