#include "Pipeline.h"

RunCheckpoint* Pipeline::createCheckpoint() {
    return new RunCheckpoint(stage, records);
}

void Pipeline::restore(RunCheckpoint* checkpoint) {
    if(checkpoint != nullptr) {
        records = checkpoint->getRecords();
        stage = checkpoint->getStage();
    }
}