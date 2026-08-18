#ifndef HAZARD_H
#define HAZARD_H

#include <iostream>
class Hazard
{
public:
    virtual void exploreHazard() = 0;
    virtual ~Hazard() = default;
};

#endif