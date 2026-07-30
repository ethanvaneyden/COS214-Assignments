#ifndef PIPELINE_H
#define PIPELINE_H

#include "RunCheckpoint.h"
#include <vector>

class Pipeline {
    protected: 
    int stage;
    std::vector<std::string> records;
    public:
    RunCheckpoint* createCheckpoint();
    void restore(RunCheckpoint*);
};

#endif