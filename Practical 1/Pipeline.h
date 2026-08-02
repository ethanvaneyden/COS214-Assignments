#ifndef PIPELINE_H
#define PIPELINE_H

#include "RunCheckpoint.h"
#include "ConnectorFactory.h"
#include "Transformation.h"
#include <vector>

class Pipeline {
    protected: 
        int stage; //Mr E
        std::vector<std::string> records; //Mr E
        ConnectorFactory* factory;
        std::vector<Transformation*> steps;
        void connect();
        virtual void extract() = 0;
        void transform();
        virtual void load() = 0;

    public:
        RunCheckpoint* createCheckpoint(); //Mr E
        void restore(RunCheckpoint*); //Mr E
        Pipeline(ConnectorFactory*);
        void run();
        void addStep(Transformation*);
        virtual ~Pipeline();
};

class BatchPipeline : public Pipeline {
    protected: 
        void extract() override;
        void load() override;
};

class StreamingPipeline : public Pipeline {
    protected: 
        void extract();
        void load();
};

#endif