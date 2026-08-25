#include "KeyNoteArea.h"
#include "BackgroundTimer.h"
#include "TechSignal.h"
#include "Technician.h"

KeyNoteArea::KeyNoteArea(std::string name) 
    : areaName(name), isOpen(true), presenterIndex(0), onDutyIndex(0) {
    onDuty = {
        Technician("Stephen Groos", "082 555 1234"),
        Technician("John MacMillan", "084 742 9051"),
        Technician("Njabulo Sishebo", "083 123 4567"),
        Technician("Moaltegi Tlhabane", "083 987 6543"),
        Technician("Anthoni van Nordy", "082 111 2222"),
        Technician("Montechristo Delgado", "084 555 6666")
    };

    presenters = {
        "Satoshi Nakamoto", "Marti Stair", "Zink Weiss",
        "Fiorello Rocco", "Lorato Ramatlapeng"
    };
}

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

    // If a power failure occurred before startTimers() was called,
    // ensure presenter rotation is held in the paused state.
    if (!isOpen) {
        pausePresenting();
    }
}

void KeyNoteArea::stopTimers()
{
    presenterTimer.stop();
    onDutyTimer.stop();
}

void KeyNoteArea::pausePresenting()
{
    presenterTimer.pause();
}

void KeyNoteArea::resumePresenting()
{
    presenterTimer.resume();
}

void KeyNoteArea::advancePresenter()
{
    if (presenters.empty()) return;
    size_t next = (presenterIndex.load(std::memory_order_relaxed) + 1) % presenters.size();
    presenterIndex.store(next, std::memory_order_relaxed);
}

void KeyNoteArea::advanceOnDuty()
{
    if (onDuty.empty()) return;
    size_t next = (onDutyIndex.load(std::memory_order_relaxed) + 1) % onDuty.size();
    onDutyIndex.store(next, std::memory_order_relaxed);
}

std::string KeyNoteArea::getPresenter() const
{
    if (isOpen && !presenters.empty()) {
        return presenters[presenterIndex.load(std::memory_order_relaxed)];
    }
    return "Area is closed. No presenter available.";
}

std::string KeyNoteArea::getOnDuty() const
{
    if (onDuty.empty()) return "No technician on duty.";
    return onDuty[onDutyIndex.load(std::memory_order_relaxed)];
}

std::string KeyNoteArea::getStatus() const
{
    return status;
}

void KeyNoteArea::update(const TechSignal &signal)
{
    TechSignal::Type type = signal.getType();
    switch (type) {
        case TechSignal::Type::UNKNOWN:
            status = "Unknown signal received.";
            break;
        case TechSignal::Type::OPEN:
            status = "Area " + areaName + " is now open.";
            isOpen = true;
            resumePresenting();
            break;
        case TechSignal::Type::CLOSED:
            status = "Area " + areaName + " is now closed.";
            isOpen = false;
            stopTimers();
            break;
        case TechSignal::Type::FULL_CAPACITY:
            status = "Area " + areaName + " has reached full capacity.";
            break;
        case TechSignal::Type::SCHEDULE_CHANGE:
            status = "Schedule change in " + areaName + ".\n Please contact the technician on duty: " + getOnDuty();
            break;
        case TechSignal::Type::POWER_FAILURE: 
            status = "Power failure in " + areaName + ".\n Please contact the technician on duty: " + getOnDuty();
            isOpen = false;
            pausePresenting();
            break;
        case TechSignal::Type::EMERGENCY_PAUSE:
            status = "Emergency pause in " + areaName + ".\n Please contact the technician on duty: " + getOnDuty();
            pausePresenting();
            break;
        default:
            break;
    }
}