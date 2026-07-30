#include "TransformationRegistry.h"

void TransformationRegistry::registerStep(std::string key, Transformation* prototype){
    if(prototype == nullptr) return;

    auto it = this->prototypes.find(key);
    if(it != this->prototypes.end()){
        //prototype found
        if(it->second != nullptr)
            delete it->second;
    }
    
    this->prototypes[key] = prototype;
}

Transformation* TransformationRegistry::create(std::string key){
    auto it = this->prototypes.find(key);
    if(it != this->prototypes.end()){
        //prototype found
        return it->second->clone();
    }
    
    return nullptr;
}

TransformationRegistry::~TransformationRegistry(){
    // obj.first is the key, obj.second is the value
    for(const auto& obj : this->prototypes){
        if(obj.second != nullptr)
            delete obj.second;
    }

    //this->prototypes.clear();
}


