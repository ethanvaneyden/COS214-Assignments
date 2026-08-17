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

        virtual void add(Map* child) override;
        virtual void remove(Map* child) override;
        virtual Map* getChild(int index) const override;
        virtual int getChildCount() const override;

        ~MapDecorator() override;
};

#endif