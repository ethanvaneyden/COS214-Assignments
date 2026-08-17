#ifndef HAZARDDECORATOR_H
#define HAZARDDECORATOR_H

#include "MapDecorator.h"

class HazardDecorator : public MapDecorator{
    public:
        HazardDecorator(Map* place);

        void describe() const override;
        bool hasDecorator(const std::string& name) const override;

        ~HazardDecorator() override;
};

#endif