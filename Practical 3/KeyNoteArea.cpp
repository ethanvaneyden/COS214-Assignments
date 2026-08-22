#include "KeyNoteArea.h"
#include "BackgroundTimer.h"
#include "TechSignal.h"


KeyNoteArea::KeyNoteArea(std::string name) : areaName(name), isOpen(false),
    presenterIndex(0), onDutyIndex(0) {}

void KeyNoteArea::startTimers()
{
    presenterTimer.start(
        std::chrono::minutes(2), 
        [this]() { advancePresenter(); }
    );

    onDutyTimer.start(
        std::chrono::minutes(5),
        [this]() { advanceOnDuty(); }
    );

}

void KeyNoteArea::stopTimers()
{
    presenterTimer.stop();
    onDutyTimer.stop();
}

void KeyNoteArea::advancePresenter()
{
    size_t next = (presenterIndex.load(std::memory_order_relaxed) + 1) % presenters.size();
    presenterIndex.store(next, std::memory_order_relaxed);
}

void KeyNoteArea::advanceOnDuty()
{
    size_t next = (onDutyIndex.load(std::memory_order_relaxed) + 1) % presenters.size();
    onDutyIndex.store(next, std::memory_order_relaxed);
}

std::string KeyNoteArea::getPresenter() const
{
    if (isOpen) 
        return presenters[presenterIndex.load(std::memory_order_relaxed)];
    return areaName + " is currently not presenting";
}

std::string KeyNoteArea::getOnDuty() const
{
    return onDuty[onDutyIndex.load(std::memory_order_relaxed)];;
}

void KeyNoteArea::update(const TechSignal &signal)
{
    TechSignal::Type type = signal.getType();
    switch (type) {
        POWER_FAILURE : 
            isOpen = false;
            status = "Power failure in " + areaName;
            break;
    }
}
