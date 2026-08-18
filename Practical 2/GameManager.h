#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>

class Traveller;
class TravelState;
class Map;
class BiomeFactory;
class Trip;
class RouteStrategy;

class GameManager{
    private:
        Traveller* traveller;
        Map* world;
        Trip* trip;

    public:
        GameManager();
        ~GameManager();

        void setWorld(Map* world);
        Map* getWorld() const;

        void setTraveller(Traveller* traveller);
        Traveller* getTraveller() const;

        void setTrip(Trip* trip);
        Trip* getTrip() const;

        void setState(TravelState* state);
        TravelState* getState() const;

        void displayStateMenu();
        void handleInput(std::string input);

        void assignBiome(Map* location, BiomeFactory* factory);
};

#endif