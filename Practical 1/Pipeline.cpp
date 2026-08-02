#include "Pipeline.h"

RunCheckpoint* Pipeline::createCheckpoint() { //Mr E
    return new RunCheckpoint(stage, records);
}

void Pipeline::restore(RunCheckpoint* checkpoint) { //Mr E
    if(checkpoint != nullptr) {
        records = checkpoint->getRecords();
        stage = checkpoint->getStage();
    }
}

Pipeline::Pipeline(ConnectorFactory* factory)
    : stage(0), factory(factory)
{}

void Pipeline::addStep(Transformation* proto){
    this->steps.push_back(proto);
}

void Pipeline::run(){
    connect();
    extract(); 
    transform(); 
    load();
}

void Pipeline::connect(){
    Connector* c = factory->createConnector();

    if(c != nullptr){
        std::cout << "Connecting to " << c->getSource() << std::endl;
        this->stage = 1;    
        delete c;
    }
}

void Pipeline::transform(){
    for(auto t : this->steps){
        this->records = t->apply(this->records);
    }
    this->stage = 3; 
}

Pipeline::~Pipeline(){
    if(this->factory != nullptr)
        delete this->factory;

    for(auto t : this->steps){
        if(t != nullptr)
            delete t;
    }
}


/////class BatchPipeline ////////////////////////////////////////
BatchPipeline::BatchPipeline(ConnectorFactory* factory)
    : Pipeline(factory)
{}

void BatchPipeline::extract(){
    Connector* c = this->factory->createConnector();
    if(c != nullptr){
        this->records = c->extract();
        std::cout << "Batch extract: " << this->records.size() << " records" << std::endl;
        this->stage= 2;
        delete c;
    }    
}

void BatchPipeline::load(){
    std::cout << "Batch load: " << this->records.size() << " records written" << std::endl;
    this->stage= 4;
}


/////class StreamingPipeline ////////////////////////////////////////
StreamingPipeline::StreamingPipeline(ConnectorFactory* factory)
    : Pipeline(factory)
{}

void StreamingPipeline::extract(){
    Connector* c = this->factory->createConnector();
    if(c != nullptr){
        this->records = c->extract();
        std::cout << "Streaming extract: " << this->records.size() << " records" << std::endl;
        this->stage= 2;
        delete c;
    }   
}

void StreamingPipeline::load(){
    std::cout << "Streaming load: " << this->records.size() << " records streamed" << std::endl;
    this->stage= 4;
}
