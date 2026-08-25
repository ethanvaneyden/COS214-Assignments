#include "KeyNoteArea.h"

KeyNoteArea::KeyNoteArea(
    std::string name,
    const std::vector<std::string> &presenters,
    const std::vector<Technician> &onDuty,
    std::chrono::minutes presenterInterval,
    std::chrono::minutes onDutyInterval ) 
    : SignalSubscriber(name, presenters, onDuty, presenterInterval, onDutyInterval) {}

void KeyNoteArea::update(const TechSignal &signal) {
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