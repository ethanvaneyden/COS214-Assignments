#include "DeduplicateStep.h"

DeduplicateStep::DeduplicateStep() : Transformation("dedup"){
}

Transformation* DeduplicateStep::clone(){
    return new DeduplicateStep();
}

std::vector<std::string> DeduplicateStep::apply(std::vector<std::string> arrayP){
    const int size = arrayP.size();
    std::vector<std::string> arrayR;
    
    if(size == 0){
        return arrayR;
    }
       
    std::string curr = arrayP[0];
    arrayR.push_back(curr);

    for(int k = 1; k < size; k++){
        if(curr == arrayP[k]){
            continue;
        }
    
        curr = arrayP[k];
        arrayR.push_back(curr);
    }

    return arrayR;
}