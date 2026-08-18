#include "Map.h"

Map::Map(const std::string &name, double distance)
    : name(name), distance(0.0)
{
    setDistance(distance);
}

void Map::add(Map *child)
{
    (void)child;
    // base implementation as location doesn't have children
    // nothing to add
}

void Map::remove(Map *child)
{
    (void)child;
    // base implementation as location doesn't have children
    // nothing to remove
}

std::string Map::getName() const
{
    return this->name;
}
Map *Map::getChild(int index) const
{
    (void)index;
    // base implementation as location doesn't have children
    return nullptr;
}
int Map::getChildCount() const
{
    return 0;
}

double Map::getDistance() const
{
    return this->distance;
}

void Map::setDistance(double distance)
{
    if (distance < 0)
    {
        std::cout << "Invalid distance. Distance cannot be negative.\n";
        return;
    }

    this->distance = distance;
}

bool Map::hasDecorator(const std::string &name) const
{
    (void)name;
    return false;
}

Map *Map::nextLocation()
{
    return nullptr;
}

Map *Map::nextPlanet()
{
    return nullptr;
}

void Map::setBiome(Biome *biome)
{
    (void)biome;
    // Base implementation: do nothing.
    // Leaf nodes (Location) override this to store biome.
    // Composite nodes (Region) can inherit this default behavior.
}

Biome *Map::getCurrentBiome()
{
    return nullptr;
}

Map::~Map()
{
    // Nothing to delete,,,
}