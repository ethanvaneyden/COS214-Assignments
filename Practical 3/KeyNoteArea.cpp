#include "KeyNoteArea.h"

using namespace std::chrono;

KeyNoteArea::KeyNoteArea(
    const std::vector<std::string> &presenters,
    const std::vector<Technician> &onDuty,
    minutes presenterInterval,
    minutes onDutyInterval 
) 
    : SignalSubscriber(presenters, onDuty, presenterInterval, onDutyInterval) {}

void KeyNoteArea::update(const TechSignal &signal) {
    TechSignal::Type type = signal.getType();
    switch (type) {
        case TechSignal::Type::UNKNOWN:
            status = "Unknown signal received.";
            break;
        case TechSignal::Type::OPEN:
            status = "Key Note Area is now open.";
            isOpen = true;
            resumePresenting();
            break;
        case TechSignal::Type::CLOSED:
            status = "Key Note Area is now closed.";
            isOpen = false;
            stopTimers();
            break;
        case TechSignal::Type::FULL_CAPACITY:
            status = "Key Note Area has reached full capacity.";
            break;
        case TechSignal::Type::SCHEDULE_CHANGE:
            status = "Schedule change in Key Note Area.\n Please contact the technician on duty: " + getOnDuty();
            break;
        case TechSignal::Type::POWER_FAILURE:
            status = "Power failure in Key Note Area.\n Please contact the technician on duty: " + getOnDuty();
            isOpen = false;
            pausePresenting();
            break;
        case TechSignal::Type::EMERGENCY_PAUSE:
            status = "Emergency pause in Key Note Area.\n Please contact the technician on duty: " + getOnDuty();
            pausePresenting();
            break;
        default:
            break;
    }
}