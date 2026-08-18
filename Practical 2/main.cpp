#include "Map.h"
#include "Location.h"
#include "Region.h"
#include "MapDecorator.h"
#include "SpaceportDecorator.h"
#include "HazardDecorator.h"
#include "ResourceDecorator.h"

#include <iostream>

using namespace std;

void testComposite();

int main(){
    testComposite();
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