#ifndef TRANSFORMATIONREGISTRY_H
#define TRANSFORMATIONREGISTRY_H
    
// vector, string, iostream and map
#include <map>
#include <string>
#include "Transformation.h"

class TransformationRegistry{
    std::map<std::string, Transformation*> prototypes;

    public:
        void registerStep(std::string, Transformation*);
        Transformation* create(std::string);
        ~TransformationRegistry();
};

#endif