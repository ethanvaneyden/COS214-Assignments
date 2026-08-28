#include "MainStage.h"
#include "BackgroundTimer.h"
#include "Technician.h"
#include "TechSignal.h"
#include <algorithm>

MainStage::MainStage(SignalSubscriber* parent)
    : SignalSubscriber(parent),
      staffIndex(0),
      staffInterval(std::chrono::minutes(5)),
      staffTimer(new BackgroundTimer()) {
    staff = {
        Technician("Stephen Groos", "082 555 1234"),
        Technician("John MacMillan", "084 742 9051"),
        Technician("Njabulo Sishebo", "083 123 4567"),
        Technician("Moaltegi Tlhabane", "083 987 6543"),
        Technician("Anthoni van Nordy", "082 111 2222"),
        Technician("Montechristo Delgado", "084 555 6666")
    };
}

MainStage::~MainStage() {
    delete staffTimer;
}

void MainStage::add(SignalSubscriber* subscriber) {
    if (subscriber && std::find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
        subscribers.push_back(subscriber);
        subscriber->setParent(this);
    }
}

void MainStage::remove(SignalSubscriber* subscriber) {
    auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
    if (it != subscribers.end()) {
        (*it)->setParent(nullptr);
        subscribers.erase(it);
    }
}

void MainStage::update(const TechSignal &signal) {
    for (SignalSubscriber* sub : subscribers) {
        if (sub) {
            sub->update(signal);
        }
    }
}

void MainStage::startStaffTimer() {
    if (!staffTimer->isRunning()) {
        staffTimer->start(staffInterval, [this]() { advanceStaff(); });
    }
}

void MainStage::stopStaffTimer() {
    if (staffTimer->isRunning()) {
        staffTimer->stop();
    }
}

void MainStage::advanceStaff() {
    if (staff.empty()) return;
    size_t next = (staffIndex.load(std::memory_order_relaxed) + 1) % staff.size();
    staffIndex.store(next, std::memory_order_relaxed);
}

std::string MainStage::getStaff() const {
    if (staff.empty()) {
        // Fallback to parent hierarchy if local staff list is empty
        return SignalSubscriber::getStaff();
    }
    return staff[staffIndex.load(std::memory_order_relaxed)];
}