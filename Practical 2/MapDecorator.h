#ifndef MAPDECORATOR_H
#define MAPDECORATOR_H

#include "Map.h"

class MapDecorator : public Map{
    protected:
        Map* wrapped;  // OWNED by this decorator!

    public:
        MapDecorator(Map* place);

        std::string getName() const override;
        void describe() const override;
        int getPopulation() const override;
        void growPopulation(int amount);
        void decreasePopulation(int amount);

        ~MapDecorator() override;
};

#endif