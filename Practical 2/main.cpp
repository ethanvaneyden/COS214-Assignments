#include "Map.h"
#include "Location.h"
#include "Region.h"
#include "MapDecorator.h"
#include "SpaceportDecorator.h"
#include "HazardDecorator.h"
#include "ResourceDecorator.h"
#include "Biome.h"
#include "BiomeFactory.h"
#include "ForestFactory.h"
#include "DesertFactory.h"
#include "RouteStrategy.h"
#include "DirectRoute.h"
#include "SafeRoute.h"
#include "ScenicRoute.h"
#include "Trip.h"
#include "TravelState.h"
#include "WalkState.h"
#include "RoverState.h"
#include "ShipState.h"
#include "Traveller.h"
#include "GameManager.h"

#include <iostream>

using namespace std;

void testComposite();
void testDecorator();
void testAbstractFactory();
void testStrategy();
void testState();
void testGameManager();
void runGame();
void showHelpText();
void printStatus(const Map *currentPlanet, const Location *currentLocation);
void applyRouteDistance(Trip *trip, double moveDistance, const std::string &unit = "KM");

struct GameContext
{
    Map *currentPlanet;
    int currentPlanetIndex;
    int currentSectionIndex;
    Location *currentLocation;
};

int main()
{
    testComposite();
    testDecorator();
    testAbstractFactory();
    testStrategy();
    testState();
    testGameManager();
    runGame();

    return 0;
}

void showHelpText()
{
    cout << "\n=== COMMANDS ===" << endl;
    cout << "  help   - Show this command list" << endl;
    cout << "  walk   - Explore on foot" << endl;
    cout << "  rover  - Travel between sections on the current planet" << endl;
    cout << "  ship   - Travel between planets with a spaceport" << endl;
    cout << "  move   - Move in the active travel mode" << endl;
    cout << "  direct - Use the direct route" << endl;
    cout << "  safe   - Use the safe route" << endl;
    cout << "  scenic - Use the scenic route" << endl;
    cout << "  speak  - Interact with the biome" << endl;
    cout << "  treasure / hazard / landmark" << endl;
    cout << "  quit   - Exit the game" << endl;
    cout << "================" << endl;
}

void printStatus(const Map *currentPlanet, const Location *currentLocation)
{
    if (currentPlanet == nullptr || currentLocation == nullptr)
    {
        return;
    }

    cout << "\n[STATUS] Planet: " << currentPlanet->getName()
         << " | Section: " << currentLocation->getName()
         << " | Population: " << currentLocation->getPopulation() << endl;
}

void applyRouteDistance(Trip *trip, double moveDistance, const std::string &unit)
{
    if (trip == nullptr)
    {
        return;
    }

    trip->setBaseDistance(moveDistance > 0 ? moveDistance : 100.0);
    if (trip->getStrategy() != nullptr)
    {
        cout << "\n>>> Calculating route..." << endl;
        trip->getStrategy()->printMessage(trip, unit);
        cout << endl;
    }
}

void runGame()
{
    // Structured world: Solar System -> Planet -> Section
    // Some planets have spaceports, others do not.
    Map *solarSystem = new Region("Solar System", 0.0);
    Map *earthPlanet = new SpaceportDecorator(new Region("Earth", 0.0));
    Map *marsPlanet = new SpaceportDecorator(new Region("Mars", 0.0));
    Map *venusPlanet = new Region("Venus", 0.0);
    Map *mercuryPlanet = new Region("Mercury", 0.0);
    Map *jupiterPlanet = new Region("Jupiter", 0.0);
    Map *saturnPlanet = new SpaceportDecorator(new Region("Saturn", 0.0));
    Map *uranusPlanet = new Region("Uranus", 0.0);
    Map *neptunePlanet = new SpaceportDecorator(new Region("Neptune", 0.0));

    Location *earthCity = new Location("City Centre", 1200, 1.0);
    Location *earthForest = new Location("Forest Belt", 850, 2.0);
    Location *earthRidge = new Location("South Ridge", 430, 3.0);

    Location *marsCrater = new Location("Crater Basin", 700, 12.0);
    Location *marsDunes = new Location("Dust Plains", 380, 14.0);
    Location *marsCanyon = new Location("Canyon Run", 260, 15.0);

    Location *venusStorm = new Location("Storm Front", 640, 18.0);
    Location *venusCanopy = new Location("Cloud Belt", 500, 19.0);
    Location *venusCavern = new Location("Cavern Plain", 300, 20.0);

    Location *mercuryCracks = new Location("Cracked Plains", 220, 25.0);
    Location *mercuryDome = new Location("Sunward Dome", 180, 26.0);
    Location *mercurySlope = new Location("Ash Slope", 120, 27.0);

    Location *jupiterHalo = new Location("Storm Halo", 900, 30.0);
    Location *jupiterCloud = new Location("Cloud Arc", 720, 31.0);
    Location *jupiterRing = new Location("Ring Gate", 480, 32.0);

    Location *saturnField = new Location("Ring Field", 610, 35.0);
    Location *saturnBasin = new Location("Basin Reach", 440, 36.0);
    Location *saturnVault = new Location("Vault Step", 260, 37.0);

    Location *uranusHollow = new Location("Ice Hollow", 360, 40.0);
    Location *uranusTide = new Location("Tide Basin", 290, 41.0);
    Location *uranusGlow = new Location("Glow Shelf", 200, 42.0);

    Location *neptuneTrench = new Location("Deep Trench", 540, 45.0);
    Location *neptuneVent = new Location("Vent Field", 420, 46.0);
    Location *neptuneShelf = new Location("Shelf Edge", 310, 47.0);

    earthPlanet->add(earthCity);
    earthPlanet->add(earthForest);
    earthPlanet->add(earthRidge);

    marsPlanet->add(marsCrater);
    marsPlanet->add(marsDunes);
    marsPlanet->add(marsCanyon);

    venusPlanet->add(venusStorm);
    venusPlanet->add(venusCanopy);
    venusPlanet->add(venusCavern);

    mercuryPlanet->add(mercuryCracks);
    mercuryPlanet->add(mercuryDome);
    mercuryPlanet->add(mercurySlope);

    jupiterPlanet->add(jupiterHalo);
    jupiterPlanet->add(jupiterCloud);
    jupiterPlanet->add(jupiterRing);

    saturnPlanet->add(saturnField);
    saturnPlanet->add(saturnBasin);
    saturnPlanet->add(saturnVault);

    uranusPlanet->add(uranusHollow);
    uranusPlanet->add(uranusTide);
    uranusPlanet->add(uranusGlow);

    neptunePlanet->add(neptuneTrench);
    neptunePlanet->add(neptuneVent);
    neptunePlanet->add(neptuneShelf);

    solarSystem->add(earthPlanet);
    solarSystem->add(marsPlanet);
    solarSystem->add(venusPlanet);
    solarSystem->add(mercuryPlanet);
    solarSystem->add(jupiterPlanet);
    solarSystem->add(saturnPlanet);
    solarSystem->add(uranusPlanet);
    solarSystem->add(neptunePlanet);

    // Travel states and trip
    TravelState *walk = new WalkState();
    TravelState *rover = new RoverState();
    TravelState *ship = new ShipState();

    RouteStrategy *direct = new DirectRoute();
    RouteStrategy *safe = new SafeRoute();
    RouteStrategy *scenic = new ScenicRoute();
    Trip *trip = new Trip(direct, 100);

    Traveller *traveller = new Traveller(walk, earthCity, earthPlanet);

    GameManager *gm = new GameManager();
    gm->setWorld(solarSystem);
    gm->setTraveller(traveller);
    gm->setTrip(trip);

    BiomeFactory *forestFactory = new ForestFactory();
    BiomeFactory *desertFactory = new DesertFactory();

    gm->assignBiome(earthCity, forestFactory);
    gm->assignBiome(earthForest, forestFactory);
    gm->assignBiome(earthRidge, forestFactory);
    gm->assignBiome(marsCrater, desertFactory);
    gm->assignBiome(marsDunes, desertFactory);
    gm->assignBiome(marsCanyon, desertFactory);

    GameContext context = {earthPlanet, 0, 0, earthCity};
    Map *planets[8] = {earthPlanet, marsPlanet, venusPlanet, mercuryPlanet, jupiterPlanet, saturnPlanet, uranusPlanet, neptunePlanet};

    cout << "\n========================================" << endl;
    cout << "   WELCOME TO SPACE EXPLORER!          " << endl;
    cout << "========================================" << endl;
    cout << "A solar system explorer game built on regions, locations, and travel states." << endl;
    cout << "Structure: Solar System -> Planet -> Section" << endl;
    cout << "There are 8 planets in this solar system." << endl;
    cout << "Only planets with a spaceport can be boarded by ship." << endl;
    cout << "You begin on Earth in the City Centre." << endl;
    cout << "========================================" << endl;
    showHelpText();
    printStatus(context.currentPlanet, context.currentLocation);

    string command;
    while (true)
    {
        gm->displayStateMenu();
        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "quit")
        {
            cout << "\nThank you for playing Space Explorer!" << endl;
            break;
        }

        if (command == "help")
        {
            showHelpText();
            continue;
        }

        if (command == "direct")
        {
            trip->setStrategy(direct);
            cout << "\n>>> Route set: Direct Route" << endl;
            continue;
        }
        if (command == "safe")
        {
            trip->setStrategy(safe);
            cout << "\n>>> Route set: Safe Route" << endl;
            continue;
        }
        if (command == "scenic")
        {
            trip->setStrategy(scenic);
            cout << "\n>>> Route set: Scenic Route" << endl;
            continue;
        }

        if (command == "walk")
        {
            if (traveller->setState(walk, "walk"))
            {
                cout << "\n>>> Travel mode: Walking on foot." << endl;
            }
            else
            {
                cout << "\n>>> You cannot transition to walking from your current mode here." << endl;
            }
            continue;
        }
        if (command == "rover")
        {
            if (traveller->setState(rover, "rover"))
            {
                cout << "\n>>> Travel mode: Rover activated." << endl;
            }
            else
            {
                cout << "\n>>> You cannot disembark here. This planet has no spaceport." << endl;
            }
            continue;
        }
        if (command == "ship")
        {
            if (traveller->setState(ship, "ship"))
            {
                cout << "\n>>> Travel mode: Ship activated." << endl;
            }
            else
            {
                cout << "\n>>> This planet has no spaceport. You cannot board the ship here." << endl;
            }
            continue;
        }

        if (command == "move")
        {
            if (gm->getState() == nullptr)
            {
                cout << "\n>>> You must choose a travel mode before moving." << endl;
                continue;
            }

            gm->handleInput(command);

            if (gm->getState() == rover)
            {
                int sectionCount = context.currentPlanet->getChildCount();
                if (sectionCount <= 0)
                {
                    cout << "\n>>> There are no sections on this planet." << endl;
                    continue;
                }

                double moveDistance = context.currentLocation != nullptr ? context.currentLocation->getDistance() : 100.0;
                applyRouteDistance(trip, moveDistance, gm->getState()->getDistanceUnit());

                context.currentSectionIndex = (context.currentSectionIndex + 1) % sectionCount;
                context.currentLocation = dynamic_cast<Location *>(context.currentPlanet->getChild(context.currentSectionIndex));
                if (context.currentLocation == nullptr)
                {
                    cout << "\n>>> Movement failed." << endl;
                    continue;
                }

                traveller->setCurrentPlace(context.currentLocation);
                cout << "\n>>> You moved to the next section on " << context.currentPlanet->getName() << "." << endl;
                printStatus(context.currentPlanet, context.currentLocation);
                continue;
            }

            if (gm->getState() == ship)
            {
                int nextIndex = (context.currentPlanetIndex + 1) % 8;
                double moveDistance = context.currentPlanet != nullptr ? context.currentPlanet->getDistance() : 100.0;
                applyRouteDistance(trip, moveDistance, gm->getState()->getDistanceUnit());

                context.currentPlanetIndex = nextIndex;
                context.currentPlanet = planets[context.currentPlanetIndex];
                traveller->setCurrentPlanet(context.currentPlanet);
                context.currentSectionIndex = 0;
                context.currentLocation = dynamic_cast<Location *>(context.currentPlanet->getChild(context.currentSectionIndex));

                if (context.currentLocation == nullptr)
                {
                    cout << "\n>>> No valid section found on that planet." << endl;
                    continue;
                }

                traveller->setCurrentPlace(context.currentLocation);
                cout << "\n>>> Travel complete: you arrived at " << context.currentPlanet->getName() << "." << endl;
                if (!context.currentPlanet->hasDecorator("spaceport"))
                {
                    cout << "\n>>> You are on a planet without a spaceport. You may travel onward, but you cannot disembark here." << endl;
                }
                printStatus(context.currentPlanet, context.currentLocation);
                continue;
            }

            cout << "\n>>> You must be in rover or ship mode to move." << endl;
            continue;
        }

        if (!command.empty())
        {
            gm->handleInput(command);
            Map *updatedLocation = traveller->getCurrentPlace();
            if (updatedLocation != nullptr)
            {
                context.currentLocation = dynamic_cast<Location *>(updatedLocation);
                if (context.currentLocation != nullptr)
                {
                    printStatus(context.currentPlanet, context.currentLocation);
                }
            }
        }
        else
        {
            cout << "\n>>> No command entered. Type 'help' to see available actions." << endl;
        }
    }

    delete gm;
    delete direct;
    delete safe;
    delete scenic;
    delete forestFactory;
    delete desertFactory;
    delete walk;
    delete rover;
    delete ship;

    cout << "========================================" << endl;
}

void testComposite()
{
    cout << "\n====================  COMPOSITE PATTERN TESTING  ====================\n";

    cout << "Creating Locations\n";

    Location *earth = new Location("Earth", 1000, 10.0);
    Location *mars = new Location("Mars", 500, 20.0);
    Location *moon = new Location("Moon", 100, 5.0);
    Location *jupiter = new Location("Jupiter", 800, 40.0);

    cout << "Earth name: " << earth->getName() << endl;
    cout << "Earth population: " << earth->getPopulation() << endl;
    cout << "Earth distance: " << earth->getDistance() << endl;
    cout << endl;

    cout << "Location describe()\n";
    earth->describe();
    mars->describe();
    moon->describe();
    cout << endl;

    cout << "Growing population\n";
    earth->growPopulation(500);
    cout << endl;

    cout << "Invalid population growth\n";
    earth->growPopulation(-100);
    cout << endl;

    cout << "Decreasing population\n";
    earth->decreasePopulation(200);
    cout << endl;

    cout << "Invalid population decrease\n";
    earth->decreasePopulation(-50);
    cout << endl;

    cout << "Decreasing population below zero\n";
    moon->decreasePopulation(1000);
    cout << endl;

    cout << "Decrease population when zero\n";
    moon->decreasePopulation(50);
    cout << endl;

    cout << "Distance validation\n";
    cout << "Current Mars distance: " << mars->getDistance() << endl;
    mars->setDistance(30.0);
    cout << "New Mars distance: " << mars->getDistance() << endl;

    mars->setDistance(-20.0);
    cout << "Mars distance after invalid update: " << mars->getDistance() << endl;
    cout << endl;

    cout << "Map base Composite operations\n";
    cout << "Earth child count: " << earth->getChildCount() << endl;
    cout << "Earth child at index 0: " << earth->getChild(0) << endl;
    earth->add(mars);
    earth->remove(mars);
    cout << endl;

    cout << "Creating Region\n";
    Region solarSystem("Solar System", 0.0);

    cout << "Region name: " << solarSystem.getName() << endl;
    cout << "Region distance: " << solarSystem.getDistance() << endl;
    cout << "Initial child count: " << solarSystem.getChildCount() << endl;
    cout << endl;

    cout << "Empty Region operations\n";
    solarSystem.describe();
    cout << "Population: " << solarSystem.getPopulation() << endl;
    solarSystem.growPopulation(100);
    solarSystem.decreasePopulation(100);
    cout << endl;

    cout << "Adding children\n";
    solarSystem.add(earth);
    solarSystem.add(mars);
    solarSystem.add(moon);

    cout << "Child count: " << solarSystem.getChildCount() << endl;
    cout << endl;

    cout << "Getting children\n";
    Map *child0 = solarSystem.getChild(0);
    Map *child1 = solarSystem.getChild(1);
    Map *child2 = solarSystem.getChild(2);

    if (child0)
        cout << "Child 0: " << child0->getName() << endl;

    if (child1)
        cout << "Child 1: " << child1->getName() << endl;

    if (child2)
        cout << "Child 2: " << child2->getName() << endl;

    cout << endl;

    cout << "Invalid child indexes\n";
    Map *invalid1 = solarSystem.getChild(-1);
    Map *invalid2 = solarSystem.getChild(100);

    cout << "Child -1: " << invalid1 << endl;
    cout << "Child 100: " << invalid2 << endl;
    cout << endl;

    cout << "Region population\n";
    cout << "Region population: " << solarSystem.getPopulation() << endl;
    cout << endl;

    cout << "Region describe()\n";
    solarSystem.describe();
    cout << endl;

    cout << "Region population growth\n";
    solarSystem.growPopulation(300);
    cout << endl;

    cout << "Invalid Region growth\n";
    solarSystem.growPopulation(-100);
    cout << endl;

    cout << "Region population decrease\n";
    solarSystem.decreasePopulation(150);
    cout << endl;

    cout << "Invalid Region decrease\n";
    solarSystem.decreasePopulation(-100);
    cout << endl;

    cout << "Adding nullptr\n";
    solarSystem.add(nullptr);
    cout << endl;

    cout << "Removing nullptr\n";
    solarSystem.remove(nullptr);
    cout << endl;

    cout << "hasDecorator()\n";
    cout << "Earth has spaceport: " << earth->hasDecorator("spaceport") << endl;
    cout << "Mars has hazard: " << mars->hasDecorator("hazard") << endl;
    cout << endl;

    cout << "Removing nonexistent child\n";
    solarSystem.remove(jupiter);
    cout << endl;

    delete jupiter;

    cout << "Removing child\n";
    solarSystem.remove(mars);
    cout << "Child count after removal: " << solarSystem.getChildCount() << endl;
    cout << endl;

    cout << "Removing nonexistent child\n";
    solarSystem.remove(jupiter);
    cout << endl;

    cout << "Region after removal\n";
    solarSystem.describe();
    cout << "Population: " << solarSystem.getPopulation() << endl;
    cout << endl;

    cout << "Invalid Region distance\n";
    solarSystem.setDistance(-50.0);
    cout << "Region distance: " << solarSystem.getDistance() << endl;
    cout << endl;

    cout << "\n===================  COMPOSITE TESTING COMPLETE  =====================\n";
}

void testDecorator()
{
    cout << "\n====================  DECORATOR PATTERN TESTING  ====================\n";

    Location *mars = new Location("Mars", 500, 20.0);

    cout << "Creating Location\n";
    cout << "Name: " << mars->getName() << endl;
    cout << "Population: " << mars->getPopulation() << endl;
    cout << "Distance: " << mars->getDistance() << endl;
    cout << endl;

    cout << "Checking decorators before decoration\n";
    cout << "Spaceport: " << mars->hasDecorator("spaceport") << endl;
    cout << "Hazard: " << mars->hasDecorator("hazard") << endl;
    cout << "Resource: " << mars->hasDecorator("resource") << endl;
    cout << endl;

    cout << "Decorating with Spaceport\n";
    Map *spaceport = new SpaceportDecorator(mars);

    cout << "Spaceport: " << spaceport->hasDecorator("spaceport") << endl;
    cout << "Hazard: " << spaceport->hasDecorator("hazard") << endl;
    cout << "Resource: " << spaceport->hasDecorator("resource") << endl;
    cout << endl;

    cout << "Testing delegated operations\n";
    cout << "Name: " << spaceport->getName() << endl;
    cout << "Population: " << spaceport->getPopulation() << endl;
    cout << "Distance: " << spaceport->getDistance() << endl;
    spaceport->describe();
    cout << endl;

    cout << "Testing delegated population operations\n";
    spaceport->growPopulation(100);
    spaceport->decreasePopulation(50);
    cout << endl;

    cout << "Adding Hazard decorator\n";
    Map *hazard = new HazardDecorator(spaceport);

    cout << "Spaceport: " << hazard->hasDecorator("spaceport") << endl;
    cout << "Hazard: " << hazard->hasDecorator("hazard") << endl;
    cout << "Resource: " << hazard->hasDecorator("resource") << endl;
    cout << endl;

    cout << "Adding Resource decorator\n";
    Map *resource = new ResourceDecorator(hazard);

    cout << "Spaceport: " << resource->hasDecorator("spaceport") << endl;
    cout << "Hazard: " << resource->hasDecorator("hazard") << endl;
    cout << "Resource: " << resource->hasDecorator("resource") << endl;
    cout << endl;

    cout << "Testing stacked decorator operations\n";
    cout << "Name: " << resource->getName() << endl;
    cout << "Population: " << resource->getPopulation() << endl;
    cout << "Distance: " << resource->getDistance() << endl;
    resource->describe();
    cout << endl;

    cout << "Changing distance through decorator\n";
    cout << "Before: " << resource->getDistance() << endl;
    resource->setDistance(50.0);
    cout << "After: " << resource->getDistance() << endl;
    cout << endl;

    cout << "Invalid distance through decorator\n";
    resource->setDistance(-10.0);
    cout << "Distance: " << resource->getDistance() << endl;
    cout << endl;

    cout << "Testing decorator with Region\n";
    Region *solarSystem = new Region("Solar System", 0.0);

    solarSystem->add(new Location("Earth", 1000, 10.0));
    solarSystem->add(new Location("Moon", 100, 5.0));

    Map *decoratedRegion = new SpaceportDecorator(solarSystem);

    cout << "Region name: " << decoratedRegion->getName() << endl;
    cout << "Region population: " << decoratedRegion->getPopulation() << endl;
    cout << "Spaceport: " << decoratedRegion->hasDecorator("spaceport") << endl;
    decoratedRegion->describe();
    cout << endl;

    cout << "Testing decorator composite operations\n";
    cout << "Child count: " << decoratedRegion->getChildCount() << endl;
    cout << "Child 0: " << decoratedRegion->getChild(0)->getName() << endl;
    cout << endl;

    delete resource;
    delete decoratedRegion;

    cout << "\n===================  DECORATOR TESTING COMPLETE  =====================\n";
}

void testAbstractFactory()
{
    cout << "\n====================  ABSTRACT FACTORY TESTING  ====================\n";

    cout << "Creating Forest Factory\n";
    BiomeFactory *forestFactory = new ForestFactory();

    cout << "Creating Forest products\n";
    NPC *forestNPC = forestFactory->createNPC();
    Treasure *forestTreasure = forestFactory->createTreasure();
    Hazard *forestHazard = forestFactory->createHazard();
    Landmark *forestLandmark = forestFactory->createLandmark();

    cout << "Testing Forest NPC\n";
    forestNPC->speak();
    cout << "\n\n";

    cout << "Testing Forest Treasure\n";
    forestTreasure->treasureHunt();
    cout << "\n\n";

    cout << "Testing Forest Hazard\n";
    forestHazard->exploreHazard();
    cout << "\n\n";

    cout << "Testing Forest Landmark\n";
    forestLandmark->exploreLandmark();
    cout << "\n\n";

    delete forestNPC;
    delete forestTreasure;
    delete forestHazard;
    delete forestLandmark;

    cout << "Creating Forest Biome\n";
    Biome *forestBiome = forestFactory->createBiome();

    cout << "Testing Forest Biome\n";
    forestBiome->speakToNPC();
    cout << "\n";
    forestBiome->huntTreasure();
    cout << "\n";
    forestBiome->exploreHazard();
    cout << "\n";
    forestBiome->exploreLandmark();
    cout << "\n\n";

    delete forestBiome;
    delete forestFactory;

    cout << "Creating Desert Factory\n";
    BiomeFactory *desertFactory = new DesertFactory();

    cout << "Creating Desert products\n";
    NPC *desertNPC = desertFactory->createNPC();
    Treasure *desertTreasure = desertFactory->createTreasure();
    Hazard *desertHazard = desertFactory->createHazard();
    Landmark *desertLandmark = desertFactory->createLandmark();

    cout << "Testing Desert NPC\n";
    desertNPC->speak();
    cout << "\n\n";

    cout << "Testing Desert Treasure\n";
    desertTreasure->treasureHunt();
    cout << "\n\n";

    cout << "Testing Desert Hazard\n";
    desertHazard->exploreHazard();
    cout << "\n\n";

    cout << "Testing Desert Landmark\n";
    desertLandmark->exploreLandmark();
    cout << "\n\n";

    delete desertNPC;
    delete desertTreasure;
    delete desertHazard;
    delete desertLandmark;

    cout << "Creating Desert Biome\n";
    Biome *desertBiome = desertFactory->createBiome();

    cout << "Testing Desert Biome\n";
    desertBiome->speakToNPC();
    cout << "\n";
    desertBiome->huntTreasure();
    cout << "\n";
    desertBiome->exploreHazard();
    cout << "\n";
    desertBiome->exploreLandmark();
    cout << "\n\n";

    delete desertBiome;
    delete desertFactory;

    cout << "Testing Biome with Location\n";

    BiomeFactory *locationFactory = new ForestFactory();
    Biome *locationBiome = locationFactory->createBiome();

    Location *location = new Location(
        "Enchanted Forest",
        1000,
        25.0,
        locationBiome);

    cout << "Location: " << location->getName() << endl;
    cout << "Population: " << location->getPopulation() << endl;
    cout << "Distance: " << location->getDistance() << endl;

    cout << "Testing Location biome\n";
    location->getBiome()->speakToNPC();
    cout << "\n";
    location->getBiome()->huntTreasure();
    cout << "\n";
    location->getBiome()->exploreHazard();
    cout << "\n";
    location->getBiome()->exploreLandmark();
    cout << "\n";

    delete location;
    delete locationFactory;

    cout << "\n===================  ABSTRACT FACTORY TESTING COMPLETE  =====================\n";
}

void testStrategy()
{
    cout << "\n====================  STRATEGY PATTERN TESTING  ====================\n";

    cout << "\nCreating strategies\n";

    RouteStrategy *direct = new DirectRoute();
    RouteStrategy *safe = new SafeRoute();
    RouteStrategy *scenic = new ScenicRoute();

    cout << "Direct strategy name: " << direct->getStrategyName() << endl;

    cout << "Safe strategy name: " << safe->getStrategyName() << endl;

    cout << "Scenic strategy name: " << scenic->getStrategyName() << endl;

    cout << "\nTesting distance calculations\n";

    cout << "Direct distance (100): " << direct->calculateDistance(100) << endl;

    cout << "Safe distance (100): " << safe->calculateDistance(100) << endl;

    cout << "Scenic distance (100): " << scenic->calculateDistance(100) << endl;

    cout << "\nTesting zero distance\n";

    cout << "Direct distance (0): " << direct->calculateDistance(0) << endl;

    cout << "Safe distance (0): " << safe->calculateDistance(0) << endl;

    cout << "Scenic distance (0): " << scenic->calculateDistance(0) << endl;

    cout << "\nCreating Trip with Direct strategy\n";

    Trip *trip = new Trip(direct, 100);

    cout << "Base distance: " << trip->getBaseDistance() << endl;

    cout << "Current strategy: " << trip->getStrategy()->getStrategyName() << endl;

    cout << "\nTesting Direct strategy message\n";

    trip->getStrategy()->printMessage(trip, "KM");
    cout << endl;

    cout << "\nChanging to Safe strategy\n";

    trip->setStrategy(safe);

    cout << "Current strategy: " << trip->getStrategy()->getStrategyName() << endl;

    trip->getStrategy()->printMessage(trip, "KM");
    cout << endl;

    cout << "\nChanging to Scenic strategy\n";

    trip->setStrategy(scenic);

    cout << "Current strategy: " << trip->getStrategy()->getStrategyName() << endl;

    trip->getStrategy()->printMessage(trip, "KM");
    cout << endl;

    cout << "\nChanging base distance\n";

    trip->setBaseDistance(200);

    cout << "New base distance: " << trip->getBaseDistance() << endl;
    cout << "Direct calculation: " << direct->calculateDistance(trip->getBaseDistance()) << endl;
    cout << "Safe calculation: " << safe->calculateDistance(trip->getBaseDistance()) << endl;
    cout << "Scenic calculation: " << scenic->calculateDistance(trip->getBaseDistance()) << endl;
    cout << "\nTesting strategy after changing distance\n";

    trip->setStrategy(direct);
    trip->getStrategy()->printMessage(trip, "KM");
    cout << endl;

    trip->setStrategy(safe);
    trip->getStrategy()->printMessage(trip, "KM");
    cout << endl;

    trip->setStrategy(scenic);
    trip->getStrategy()->printMessage(trip, "KM");
    cout << endl;

    cout << "\nTesting different distance units\n";

    trip->setStrategy(direct);
    trip->getStrategy()->printMessage(trip, "AU");
    cout << endl;

    trip->setStrategy(safe);
    trip->getStrategy()->printMessage(trip, "AU");
    cout << endl;

    trip->setStrategy(scenic);
    trip->getStrategy()->printMessage(trip, "AU");
    cout << endl;

    delete trip;

    // The Trip does not own the strategies.
    // Therefore the strategies are deleted separately.
    delete direct;
    delete safe;
    delete scenic;

    cout << "\n===================  STRATEGY TESTING COMPLETE  =====================\n";
}

void testState()
{
    cout << "\n====================  STATE PATTERN TESTING  ====================\n";

    Location *earth = new Location("Earth", 1000, 10.0);
    Location *mars = new Location("Mars", 500, 20.0);
    Location *decoratedMarsLocation = new Location("Mars", 500, 20.0);

    Region *solarSystem = new Region("Solar System", 0.0);
    solarSystem->add(earth);
    solarSystem->add(mars);

    Map *spaceportMars = new SpaceportDecorator(decoratedMarsLocation);

    TravelState *walk = new WalkState();
    TravelState *rover = new RoverState();
    TravelState *ship = new ShipState();

    cout << "\nCreating states\n";
    cout << "Walk state: " << walk->getModeName() << endl;
    cout << "Rover state: " << rover->getModeName() << endl;
    cout << "Ship state: " << ship->getModeName() << endl;

    cout << "\nCreating Traveller\n";
    Traveller *traveller = new Traveller(walk, earth, solarSystem);

    cout << "Current state: " << traveller->getCurrentState()->getModeName() << endl;
    cout << "Current location: " << traveller->getCurrentPlace()->getName() << endl;

    cout << "\nTesting Walk state menu\n";
    walk->displayMenu();

    cout << "\nTesting Walk state move\n";
    walk->move(traveller);

    cout << "\nTesting Walk state commands\n";

    string input = "speak";
    walk->handleInput(input, traveller);

    input = "treasure";
    walk->handleInput(input, traveller);

    input = "hazard";
    walk->handleInput(input, traveller);

    input = "landmark";
    walk->handleInput(input, traveller);

    cout << "\nTesting invalid Walk command\n";
    input = "invalid";
    walk->handleInput(input, traveller);

    cout << "\nTesting empty Walk command\n";
    input = "";
    walk->handleInput(input, traveller);

    cout << "\nTesting Walk transitions\n";

    string target = "rover";
    cout << "Walk -> Rover: " << walk->canTransition(target, traveller->getCurrentPlace()) << endl;

    target = "ship";
    cout << "Walk -> Ship: " << walk->canTransition(target, traveller->getCurrentPlace()) << endl;

    target = "invalid";
    cout << "Walk -> Invalid: " << walk->canTransition(target, traveller->getCurrentPlace()) << endl;

    cout << "\nChanging to Rover state\n";
    traveller->setState(rover, "rover");

    cout << "Current state: " << traveller->getCurrentState()->getModeName() << endl;

    cout << "\nTesting Rover state menu\n";
    rover->displayMenu();

    cout << "\nTesting Rover state move\n";
    rover->move(traveller);

    cout << "Current location: " << traveller->getCurrentPlace()->getName() << endl;

    cout << "\nTesting Rover state commands\n";

    input = "move";
    rover->handleInput(input, traveller);

    cout << "\nTesting invalid Rover command\n";
    input = "invalid";
    rover->handleInput(input, traveller);

    cout << "\nTesting empty Rover command\n";
    input = "";
    rover->handleInput(input, traveller);

    cout << "\nTesting Rover transitions\n";

    target = "walk";
    cout << "Rover -> Walk: " << rover->canTransition(target, traveller->getCurrentPlace()) << endl;

    target = "ship";
    cout << "Rover -> Ship: " << rover->canTransition(target, traveller->getCurrentPlace()) << endl;

    target = "invalid";
    cout << "Rover -> Invalid: " << rover->canTransition(target, traveller->getCurrentPlace()) << endl;

    cout << "\nTesting Rover transition with spaceport\n";

    traveller->setCurrentPlace(spaceportMars);

    target = "ship";
    cout << "Rover -> Ship with spaceport: " << rover->canTransition(target, traveller->getCurrentPlace()) << endl;

    cout << "\nChanging to Ship state\n";
    traveller->setState(ship, "ship");

    cout << "Current state: " << traveller->getCurrentState()->getModeName() << endl;

    cout << "\nTesting Ship state menu\n";
    ship->displayMenu();

    cout << "\nTesting Ship state move\n";
    ship->move(traveller);

    cout << "Current location: " << traveller->getCurrentPlace()->getName() << endl;

    cout << "\nTesting Ship state commands\n";

    input = "move";
    ship->handleInput(input, traveller);

    cout << "\nTesting invalid Ship command\n";
    input = "invalid";
    ship->handleInput(input, traveller);

    cout << "\nTesting empty Ship command\n";
    input = "";
    ship->handleInput(input, traveller);

    cout << "\nTesting Ship transitions\n";

    target = "rover";
    cout << "Ship -> Rover: " << ship->canTransition(target, traveller->getCurrentPlace()) << endl;

    target = "invalid";
    cout << "Ship -> Invalid: " << ship->canTransition(target, traveller->getCurrentPlace()) << endl;

    cout << "\nTesting null Traveller\n";

    walk->move(nullptr);
    rover->move(nullptr);
    ship->move(nullptr);

    input = "move";
    walk->handleInput(input, nullptr);
    rover->handleInput(input, nullptr);
    ship->handleInput(input, nullptr);

    cout << "\nTesting null location\n";

    Traveller *nullLocationTraveller = new Traveller(walk, nullptr, solarSystem);

    walk->move(nullLocationTraveller);
    rover->move(nullLocationTraveller);
    ship->move(nullLocationTraveller);

    input = "speak";
    walk->handleInput(input, nullLocationTraveller);

    target = "rover";
    cout << "Walk transition with null location: " << walk->canTransition(target, nullptr) << endl;

    cout << "\nTesting Traveller setters\n";

    nullLocationTraveller->setCurrentPlace(earth);
    nullLocationTraveller->setState(ship, "ship");

    cout << "State: " << nullLocationTraveller->getCurrentState()->getModeName() << endl;

    cout << "Location: " << nullLocationTraveller->getCurrentPlace()->getName() << endl;

    delete nullLocationTraveller;

    delete traveller;

    delete walk;
    delete rover;
    delete ship;

    delete spaceportMars;

    delete solarSystem;

    cout << "\n===================  STATE TESTING COMPLETE  =====================\n";
}

void testGameManager()
{
    cout << "\n====================  GAME MANAGER TESTING  ====================\n";

    cout << "\nCreating GameManager\n";

    GameManager *manager = new GameManager();

    cout << "Testing empty GameManager\n";
    cout << "World: " << manager->getWorld() << endl;
    cout << "Traveller: " << manager->getTraveller() << endl;
    cout << "Trip: " << manager->getTrip() << endl;
    cout << "State: " << manager->getState() << endl;

    cout << "\nTesting empty manager state functions\n";
    manager->displayStateMenu();
    manager->handleInput("move");
    manager->setState(nullptr);

    cout << "\nCreating world\n";

    Region *world = new Region("Solar System", 0.0);

    Location *earth = new Location(
        "Earth",
        1000,
        10.0);

    Location *mars = new Location(
        "Mars",
        500,
        20.0);

    world->add(earth);
    world->add(mars);

    cout << "World name: " << world->getName() << endl;
    cout << "World children: " << world->getChildCount() << endl;

    cout << "\nTesting setWorld/getWorld\n";

    manager->setWorld(world);

    cout << "Manager world: "
         << manager->getWorld()->getName()
         << endl;

    cout << "Manager world population: "
         << manager->getWorld()->getPopulation()
         << endl;

    cout << "\nCreating Traveller and states\n";

    TravelState *walk = new WalkState();
    TravelState *rover = new RoverState();
    TravelState *ship = new ShipState();

    Traveller *traveller = new Traveller(
        walk,
        earth,
        world);

    cout << "Traveller state: "
         << traveller->getCurrentState()->getModeName()
         << endl;

    cout << "Traveller location: "
         << traveller->getCurrentPlace()->getName()
         << endl;

    cout << "\nTesting setTraveller/getTraveller\n";

    manager->setTraveller(traveller);

    cout << "Manager traveller: "
         << manager->getTraveller()
         << endl;

    cout << "Manager state: "
         << manager->getState()->getModeName()
         << endl;

    cout << "\nTesting GameManager state menu delegation\n";

    manager->displayStateMenu();

    cout << "\nTesting GameManager input delegation\n";

    manager->handleInput("speak");

    cout << "\nTesting GameManager setState\n";

    manager->setState(rover);

    cout << "Current state after setState: "
         << manager->getState()->getModeName()
         << endl;

    manager->displayStateMenu();

    cout << "\nChanging GameManager state to Ship\n";

    manager->setState(ship);

    cout << "Current state after setState: "
         << manager->getState()->getModeName()
         << endl;

    manager->displayStateMenu();

    cout << "\nTesting GameManager input with Ship state\n";

    manager->handleInput("move");

    cout << "\nTesting Trip with GameManager\n";

    RouteStrategy *direct = new DirectRoute();

    Trip *trip = new Trip(
        direct,
        100);

    manager->setTrip(trip);

    cout << "Trip base distance: "
         << manager->getTrip()->getBaseDistance()
         << endl;

    cout << "Trip strategy: "
         << manager->getTrip()->getStrategy()->getStrategyName()
         << endl;

    cout << "\nTesting assignBiome()\n";

    BiomeFactory *forestFactory = new ForestFactory();

    cout << "Earth biome before assignment: "
         << earth->getBiome()
         << endl;

    manager->assignBiome(
        earth,
        forestFactory);

    cout << "Earth biome after assignment: "
         << earth->getBiome()
         << endl;

    cout << "\nTesting assigned Earth biome\n";

    if (earth->getBiome() != nullptr)
    {
        earth->getBiome()->speakToNPC();

        cout << endl;

        earth->getBiome()->huntTreasure();

        cout << endl;

        earth->getBiome()->exploreHazard();

        cout << endl;

        earth->getBiome()->exploreLandmark();
    }

    cout << "\nTesting assignBiome() with nullptr location\n";

    manager->assignBiome(
        nullptr,
        forestFactory);

    cout << "Completed nullptr location test\n";

    cout << "\nTesting assignBiome() with nullptr factory\n";

    manager->assignBiome(
        mars,
        nullptr);

    cout << "Completed nullptr factory test\n";

    cout << "\nTesting assignBiome() with Region\n";

    manager->assignBiome(
        world,
        forestFactory);

    cout << "Completed Region assignment test\n";

    cout << "\nTesting null state\n";

    manager->setState(nullptr);

    cout << "State after nullptr setState: "
         << manager->getState()
         << endl;

    cout << "\nRestoring Walk state\n";

    manager->setState(walk);

    cout << "Current state: "
         << manager->getState()->getModeName()
         << endl;

    cout << "\nCleaning up GameManager\n";

    delete manager;

    // GameManager owns:
    // - traveller
    // - world
    // - trip

    // GameManager does NOT own:
    // - TravelState objects
    // - RouteStrategy objects
    // - BiomeFactory

    delete walk;
    delete rover;
    delete ship;

    delete direct;
    delete forestFactory;

    cout << "\n===================  GAMEMANAGER TESTING COMPLETE  =====================\n";
}