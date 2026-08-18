#ifndef LANDMARK_H
#define LANDMARK_H

#include <iostream>
class Landmark
{
public:
    virtual void exploreLandmark() = 0;
    virtual ~Landmark() = default;
};

#endif