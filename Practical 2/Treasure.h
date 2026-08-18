#ifndef TREASURE_H
#define TREASURE_H

#include <iostream>

class Treasure
{
public:
    virtual void treasureHunt() = 0;
    virtual ~Treasure() = default;
};

#endif