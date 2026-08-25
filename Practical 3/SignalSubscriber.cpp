#include "SignalSubscriber.h"

SignalSubscriber::SignalSubscriber(
    std::string name,
    std::vector<std::string> presenters,
    std::vector<Technician> onDuty,
    std::chrono::minutes presenterInterval,
    std::chrono::minutes onDutyInterval
) : areaName(std::move(name)),
    presenters(std::move(presenters)),
    onDuty(std::move(onDuty)),
    presenterInterval(presenterInterval),
    onDutyInterval(onDutyInterval) {}

void SignalSubscriber::startTimers() {
    presenterTimer.start(presenterInterval, [this]() { advancePresenter(); });
    onDutyTimer.start(onDutyInterval, [this]() { advanceOnDuty(); });

    if (!isOpen) {
        pausePresenting();
    }
}

void SignalSubscriber::stopTimers() {
    presenterTimer.stop();
    onDutyTimer.stop();
}

void SignalSubscriber::pausePresenting() {
    presenterTimer.pause();
}

void SignalSubscriber::resumePresenting() {
    presenterTimer.resume();
}

void SignalSubscriber::advancePresenter() {
    if (presenters.empty()) return;
    size_t next = (presenterIndex.load(std::memory_order_relaxed) + 1) % presenters.size();
    presenterIndex.store(next, std::memory_order_relaxed);
}

void SignalSubscriber::advanceOnDuty() {
    if (onDuty.empty()) return;
    size_t next = (onDutyIndex.load(std::memory_order_relaxed) + 1) % onDuty.size();
    onDutyIndex.store(next, std::memory_order_relaxed);
}

std::string SignalSubscriber::getPresenter() const {
    if (isOpen && !presenters.empty()) {
        return presenters[presenterIndex.load(std::memory_order_relaxed)];
    }
    return "Area is closed. No presenter available.";
}

std::string SignalSubscriber::getOnDuty() const {
    if (onDuty.empty()) return "No technician on duty.";
    return onDuty[onDutyIndex.load(std::memory_order_relaxed)];
}

std::string SignalSubscriber::getStatus() const {
    return status;
}