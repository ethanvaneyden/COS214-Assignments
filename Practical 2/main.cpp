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

#include <iostream>

using namespace std;

void testComposite();
void testDecorator();
void testAbstractFactory();
void testStrategy();
void testState();

int main(){
    testComposite();
    testDecorator();
    testAbstractFactory();
    testStrategy();
    testState();

    return 0;
}

void testComposite(){
    cout << "\n====================  COMPOSITE PATTERN TESTING  ====================\n";

    cout << "Creating Locations\n";

    Location* earth = new Location("Earth", 1000, 10.0);
    Location* mars = new Location("Mars", 500, 20.0);
    Location* moon = new Location("Moon", 100, 5.0);
    Location* jupiter = new Location("Jupiter", 800, 40.0);

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
    Map* child0 = solarSystem.getChild(0);
    Map* child1 = solarSystem.getChild(1);
    Map* child2 = solarSystem.getChild(2);

    if(child0)
        cout << "Child 0: " << child0->getName() << endl;

    if(child1)
        cout << "Child 1: " << child1->getName() << endl;

    if(child2)
        cout << "Child 2: " << child2->getName() << endl;

    cout << endl;

    cout << "Invalid child indexes\n";
    Map* invalid1 = solarSystem.getChild(-1);
    Map* invalid2 = solarSystem.getChild(100);

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

void testDecorator(){
    cout << "\n====================  DECORATOR PATTERN TESTING  ====================\n";

    Location* mars = new Location("Mars", 500, 20.0);

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
    Map* spaceport = new SpaceportDecorator(mars);

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
    Map* hazard = new HazardDecorator(spaceport);

    cout << "Spaceport: " << hazard->hasDecorator("spaceport") << endl;
    cout << "Hazard: " << hazard->hasDecorator("hazard") << endl;
    cout << "Resource: " << hazard->hasDecorator("resource") << endl;
    cout << endl;

    cout << "Adding Resource decorator\n";
    Map* resource = new ResourceDecorator(hazard);

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
    Region* solarSystem = new Region("Solar System", 0.0);

    solarSystem->add(new Location("Earth", 1000, 10.0));
    solarSystem->add(new Location("Moon", 100, 5.0));

    Map* decoratedRegion = new SpaceportDecorator(solarSystem);

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

void testAbstractFactory(){
    cout << "\n====================  ABSTRACT FACTORY TESTING  ====================\n";

    cout << "Creating Forest Factory\n";
    BiomeFactory* forestFactory = new ForestFactory();

    cout << "Creating Forest products\n";
    NPC* forestNPC = forestFactory->createNPC();
    Treasure* forestTreasure = forestFactory->createTreasure();
    Hazard* forestHazard = forestFactory->createHazard();
    Landmark* forestLandmark = forestFactory->createLandmark();

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
    Biome* forestBiome = forestFactory->createBiome();

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
    BiomeFactory* desertFactory = new DesertFactory();

    cout << "Creating Desert products\n";
    NPC* desertNPC = desertFactory->createNPC();
    Treasure* desertTreasure = desertFactory->createTreasure();
    Hazard* desertHazard = desertFactory->createHazard();
    Landmark* desertLandmark = desertFactory->createLandmark();

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
    Biome* desertBiome = desertFactory->createBiome();

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

    BiomeFactory* locationFactory = new ForestFactory();
    Biome* locationBiome = locationFactory->createBiome();

    Location* location = new Location(
        "Enchanted Forest",
        1000,
        25.0,
        locationBiome
    );

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

void testStrategy(){
    cout << "\n====================  STRATEGY PATTERN TESTING  ====================\n";

    cout << "\nCreating strategies\n";

    RouteStrategy* direct = new DirectRoute();
    RouteStrategy* safe = new SafeRoute();
    RouteStrategy* scenic = new ScenicRoute();

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

    Trip* trip = new Trip(direct, 100);

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

    //The Trip does not own the strategies.
    //Therefore the strategies are deleted separately.
    delete direct;
    delete safe;
    delete scenic;

    cout << "\n===================  STRATEGY TESTING COMPLETE  =====================\n";
}

void testState(){
    cout << "\n====================  STATE PATTERN TESTING  ====================\n";

    Location* earth = new Location("Earth", 1000, 10.0);
    Location* mars = new Location("Mars", 500, 20.0);
    Location* decoratedMarsLocation = new Location("Mars", 500, 20.0);

    Region* solarSystem = new Region("Solar System", 0.0);
    solarSystem->add(earth);
    solarSystem->add(mars);

    Map* spaceportMars = new SpaceportDecorator(decoratedMarsLocation);

    TravelState* walk = new WalkState();
    TravelState* rover = new RoverState();
    TravelState* ship = new ShipState();

    cout << "\nCreating states\n";
    cout << "Walk state: " << walk->getModeName() << endl;
    cout << "Rover state: " << rover->getModeName() << endl;
    cout << "Ship state: " << ship->getModeName() << endl;

    cout << "\nCreating Traveller\n";
    Traveller* traveller = new Traveller(walk, earth);

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
    traveller->setState(rover);

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
    traveller->setState(ship);

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

    Traveller* nullLocationTraveller = new Traveller(walk, nullptr);

    walk->move(nullLocationTraveller);
    rover->move(nullLocationTraveller);
    ship->move(nullLocationTraveller);

    input = "speak";
    walk->handleInput(input, nullLocationTraveller);

    target = "rover";
    cout << "Walk transition with null location: " << walk->canTransition(target, nullptr) << endl;

    cout << "\nTesting Traveller setters\n";

    nullLocationTraveller->setCurrentPlace(earth);
    nullLocationTraveller->setState(ship);

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