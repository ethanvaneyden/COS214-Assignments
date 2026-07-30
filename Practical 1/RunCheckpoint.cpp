#include "RunCheckpoint.h"

RunCheckpoint::RunCheckpoint(int stage, std::vector<std::string> records) {
    this->stage = stage;
    this->records = records;
}

std::vector<std::string> RunCheckpoint::getRecords() {
    return records;
}

int RunCheckpoint::getStage() {
    return stage;
}