#include "MainStage.h"
#include "BackgroundTimer.h"
#include "EventComposite.h"
#include "TechSignal.h"
#include "Technician.h"
#include <algorithm>
#include <iostream>

MainStage::MainStage(EventComponent *parent)
    : EventComposite("Main_Stage", parent), staffIndex(0),
      staffInterval(std::chrono::minutes(5)),
      staffTimer(new BackgroundTimer()) {
  staff = {Technician("Stephen Groos", "082 555 1234"),
           Technician("John MacMillan", "084 742 9051"),
           Technician("Njabulo Sishebo", "083 123 4567"),
           Technician("Moaltegi Tlhabane", "083 987 6543"),
           Technician("Anthoni van Nordy", "082 111 2222"),
           Technician("Montechristo Delgado", "084 555 6666")};
}

MainStage::~MainStage() { delete staffTimer; }

void MainStage::update(const TechSignal &signal) {
  broadcaster->transmit(signal);
}

void MainStage::open() {
  for (EventComponent *child : children) {
    if (child) {
      child->open();
    }
  }
  startStaffTimer();
}

void MainStage::close() {
  for (EventComponent *child : children) {
    if (child) {
      child->close();
    }
  }
  stopStaffTimer();
}

int MainStage::getCapacity() const {
  int total = 0;
  for (EventComponent *child : children) {
    if (child) {
      total += child->getCapacity();
    }
  }
  return total;
}

int MainStage::enterVisitor(int visitors) {
  if (visitors <= 0) {
    return 0;
  }

  int remaining = visitors;
  for (EventComponent *child : children) {
    if (!child) {
      continue;
    }
    int accepted = child->enterVisitor(remaining);
    remaining -= accepted;
    if (remaining <= 0) {
      break;
    }
  }
  return visitors - remaining;
}

int MainStage::leaveVisitor(int visitors) {
  if (visitors <= 0) {
    return 0;
  }

  int remaining = visitors;
  for (EventComponent *child : children) {
    if (!child) {
      continue;
    }
    int removed = child->leaveVisitor(remaining);
    remaining -= removed;
    if (remaining <= 0) {
      break;
    }
  }
  return visitors - remaining;
}

int MainStage::getCurrentVisitors() const {
  int total = 0;
  for (EventComponent *child : children) {
    if (child) {
      total += child->getCurrentVisitors();
    }
  }
  return total;
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
  if (staff.empty())
    return;
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
  for (EventComponent *child : children) {
    if (child) {
      status += child->getStatus();
    }
  }
  return status;
}