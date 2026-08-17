#ifndef RESOURCEDECORATOR_H
#define RESOURCEDECORATOR_H

#include "MapDecorator.h"
#include <iostream>

class ResourceDecorator : public MapDecorator{
    public:
        ResourceDecorator(Map* place);

        void describe() const override;
        bool hasDecorator(const std::string& name) const override;

        ~ResourceDecorator() override;
};

#endif