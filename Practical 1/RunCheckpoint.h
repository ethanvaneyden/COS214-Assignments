#ifndef RUNCHECKPOINT_H
#define RUNCHECKPOINT_H

#include "vector"
#include "string"

class RunCheckpoint {
    private:
    int stage;
    std::vector<std::string> records;

    public:
    RunCheckpoint(int, std::vector<std::string>);
    int getStage();
    std::vector<std::string> getRecords();
    
};

#endif