#include "CheckpointManager.h"

void CheckpointManager::save(RunCheckpoint *checkpoint)
{
    history.push_back(checkpoint);
}

RunCheckpoint *CheckpointManager::undo()
{
    if (history.empty())
    {
        return nullptr;
    }
    else
    {
        RunCheckpoint *lastCheckpoint = history.back();
        history.pop_back();
        return lastCheckpoint;
    }
}

CheckpointManager::~CheckpointManager()
{
    for (const auto checkpoint : history)
    {
        delete checkpoint;
    }
}