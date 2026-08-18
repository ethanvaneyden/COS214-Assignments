#ifndef MAPDECORATOR_H
#define MAPDECORATOR_H

#include "Map.h"

class MapDecorator : public Map{
    protected:
        Map* wrapped;  // OWNED by this decorator

    public:
        MapDecorator(Map* place);

        // Delegating all operations to wrapped (default behaviour)
        std::string getName() const override;
        void describe() const override;
        int getPopulation() const override;
        void growPopulation(int amount) override;
        void decreasePopulation(int amount) override;

        void add(Map* child) override;
        void remove(Map* child) override;
        Map* getChild(int index) const override;
        int getChildCount() const override;

        double getDistance() const override;
        void setDistance(double distance) override;
        bool hasDecorator(const std::string& name) const override;

        ~MapDecorator() override;
};

#endif