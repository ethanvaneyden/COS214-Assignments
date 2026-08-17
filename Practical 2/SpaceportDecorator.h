#ifndef SPACEPORTDECORATOR_H
#define SPACEPORTDECORATOR_H

#include "MapDecorator.h"

class SpaceportDecorator : public MapDecorator {
    public:
        SpaceportDecorator(Map* place);

        void describe() const override;
        bool hasDecorator(const std::string& name) const override;

        ~SpaceportDecorator() override;
};

#endif