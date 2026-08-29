#include "MainStage.h"
#include "BackgroundTimer.h"
#include "Technician.h"
#include "TechSignal.h"
#include <algorithm>

MainStage::MainStage(EventComponent* parent)
    : EventComponent(parent),
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

void MainStage::add(EventComponent* component) {
    if (component && std::find(children.begin(), children.end(), component) == children.end()) {
        children.push_back(component);
        component->setParent(this);
        subscribe(component);
    }
}

void MainStage::remove(EventComponent* component) {
    auto it = std::find(children.begin(), children.end(), component);
    if (it != children.end()) {
        (*it)->setParent(nullptr);
        unsubscribe(component);
        children.erase(it);
    }
}

void MainStage::update(const TechSignal& signal) {
    transmit(signal);
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
        return EventComponent::getStaff();
    }
    return staff[staffIndex.load(std::memory_order_relaxed)];
}

std::string MainStage::getStatus() const {
    std::string status = "-----MAIN STAGE----\n";
    for (EventComponent* child : children) {
        if (child) {
            status += child->getStatus();
        }
    }
    return status;
}