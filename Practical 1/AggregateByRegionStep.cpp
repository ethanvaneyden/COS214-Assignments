#include "AggregateByRegionStep.h"

AggregateByRegionStep::AggregateByRegionStep() : Transformation("aggregate"){
}

Transformation* AggregateByRegionStep::clone(){
    return new AggregateByRegionStep();
}

std::vector<std::string> AggregateByRegionStep::apply(std::vector<std::string> arrayP){
    std::vector<std::string> arrayR;
    std::string fullNum = "";
    int size = arrayP.size();

    if(size == 0){
        fullNum += '0'; 
    }
    else{
        while(size > 0){
            char lastNum = '0' + (size % 10); 
            fullNum = lastNum + fullNum;
            size /= 10;
        }
    }
    fullNum = "COUNT=" + fullNum;
    arrayR.push_back(fullNum);

    return arrayR;
};