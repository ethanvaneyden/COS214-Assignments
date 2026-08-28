#include "KeyNoteArea.h"
#include "TechSignal.h"
#include "BackgroundTimer.h"

using namespace std::chrono;

KeyNoteArea::KeyNoteArea() {
    presenters = { 
        "Satoshi Nakamoto", "Marti Stair", "Zink Weiss",
        "Fiorello Rocco", "Lorato Ramatlapeng"
    };
    presenterInterval = minutes(2);
    presenterIndex = 0;
    isOpen = true;
}

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
            pausePresenterTimer();
            break;
        case TechSignal::Type::EMERGENCY_PAUSE:
            status = "Emergency pause in Key Note Area.\n Please contact the technician on duty: " + getOnDuty();
            pausePresenterTimer();
            break;
        default:
            break;
    }
}

void KeyNoteArea::startPresenterTimer() {
    presenterTimer.start(presenterInterval, [this]() { advancePresenter(); });
    if (!isOpen) { pausePresenterTimer(); }
}

void KeyNoteArea::stopPresenterTimer() {
    presenterTimer.stop();
}

void KeyNoteArea::pausePresenterTimer() {
    presenterTimer.pause();
}

void KeyNoteArea::resumePresenterTimer() {
    presenterTimer.resume();
}

void KeyNoteArea::advancePresenter() {
    if (presenters.empty()) return;
    size_t next = (presenterIndex.load(std::memory_order_relaxed) + 1) % presenters.size();
    presenterIndex.store(next, std::memory_order_relaxed);
}

std::string SignalSubscriber::getPresenter() const {
    if (isOpen && !presenters.empty()) {
        return presenters[presenterIndex.load(std::memory_order_relaxed)];
    }
    return "Area is closed. No presenter available.";
}

std::string SignalSubscriber::getStatus() const {
    return status;
}