#ifndef DEDUPLICATESTEP_H
#define DEDUPLICATESTEP_H

#include <string>
#include <vector>
#include "Transformation.h"

class DeduplicateStep : public Transformation{
    public:
        DeduplicateStep();
        Transformation* clone() override;
        std::vector<std::string> apply(std::vector<std::string>) override;
};

#endif