#include "DemoArea.h"
#include "BackgroundTimer.h"
#include "TechSignal.h"
#include <algorithm>
#include <iostream>

using namespace std::chrono;

DemoArea::DemoArea(EventComponent* parent)
    : EventLeaf("Demo_Area", parent),
      isOpen(true),
      handsOnAllowed(false),
      equipmentReady(true),
      capacity(100),
      currentVisitors(0),
      demoIndex(0),
      demoTimer(new BackgroundTimer()),
      demoInterval(minutes(3)) {
    
    demoSchedule = {
        "Autonomous Drone Navigation Demo",
        "Haptic VR Surgical Glove Reveal",
        "Exoskeleton Live Test",
        "Quantum Computer Interface Pitch"
    };

    demoSpecs = {
        "Power: Battery Pack | Safety Enclosure: Active | Network: Dedicated RF",
        "Power: 110V AC | Calibration: Required | Network: Low-Latency Wi-Fi 6E",
        "Power: 220V High-Current | Hydraulics: Checked | Network: Bluetooth LE",
        "Power: Cryo-Cooling Unit | Shielding: Electromagnetic | Network: Fiber Optic"
    };

    status = "Demo Area is ready for live demonstrations.";
}

DemoArea::~DemoArea() {
    delete demoTimer;
}

void DemoArea::open() {
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        isOpen = true;
        equipmentReady = true;
        status = "Demo Area is now open.";
    }

    if (demoTimer->isPaused()) {
        resumeDemoTimer();
    } else if (!demoTimer->isRunning()) {
        startDemoTimer();
    }
}

void DemoArea::close() {
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        isOpen = false;
        handsOnAllowed = false;
        status = "Demo Area is now closed.";
    }
    stopDemoTimer();
}


int DemoArea::getCapacity() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return capacity;
}

int DemoArea::enterVisitor(int visitors) {
    std::lock_guard<std::mutex> lock(stateMutex);
    if (!isOpen || visitors <= 0) return 0;

    int availableSpace = capacity - currentVisitors;
    int admitted = std::min(visitors, availableSpace);
    currentVisitors += admitted;
    return admitted;
}

int DemoArea::leaveVisitor(int visitors) {
    std::lock_guard<std::mutex> lock(stateMutex);
    if (visitors <= 0) return 0;

    int removed = std::min(visitors, currentVisitors);
    currentVisitors -= removed;
    return removed;
}

int DemoArea::getCurrentVisitors() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return currentVisitors;
}

void DemoArea::update(const TechSignal &signal) {
    bool shouldStartTimer = false;
    bool shouldResumeTimer = false;
    bool shouldStopTimer = false;
    bool shouldPauseTimer = false;

    {
        std::lock_guard<std::mutex> lock(stateMutex);

        switch (signal.getType()) {
            case TechSignal::Type::UNKNOWN:
                status = "Unknown signal received in Demo Area.";
                break;

            case TechSignal::Type::OPEN:
                isOpen = true;
                equipmentReady = true;
                status = "Demo Area is now open.";
                if (demoTimer->isPaused()) {
                    shouldResumeTimer = true;
                } else if (!demoTimer->isRunning()) {
                    shouldStartTimer = true;
                }
                break;

            case TechSignal::Type::CLOSE:
                isOpen = false;
                handsOnAllowed = false;
                status = "Demo Area is now closed.";
                shouldStopTimer = true;
                break;

            case TechSignal::Type::FULL_CAPACITY:
                status = "Demo Area spectator zone has reached full capacity.";
                break;

            case TechSignal::Type::SCHEDULE_CHANGE:
                status = "Schedule change in Demo Area.\n Please contact the technician on duty: " + getStaff();
                break;

            case TechSignal::Type::POWER_FAILURE:
                status = "Power failure in Demo Area. Equipment safety locked.\n Please contact the technician on duty: " + getStaff();
                isOpen = false;
                equipmentReady = false;
                handsOnAllowed = false;
                shouldPauseTimer = true;
                break;

            case TechSignal::Type::EMERGENCY_PAUSE:
                status = "Emergency pause in Demo Area.\n Please contact the technician on duty: " + getStaff();
                equipmentReady = false;
                handsOnAllowed = false;
                shouldPauseTimer = true;
                break;

            default:
                break;
        }
    }

    // Execute timer transitions outside stateMutex lock to avoid deadlocks
    if (shouldResumeTimer) resumeDemoTimer();
    if (shouldStartTimer)  startDemoTimer();
    if (shouldStopTimer)   stopDemoTimer();
    if (shouldPauseTimer)  pauseDemoTimer();
}

void DemoArea::startDemoTimer() {
    demoTimer->start(demoInterval, [this]() { advanceDemo(); });
    
    bool checkOpen = false;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        checkOpen = isOpen;
    }
    if (!checkOpen) { 
        pauseDemoTimer(); 
    }
}

void DemoArea::stopDemoTimer()   { demoTimer->stop(); }
void DemoArea::pauseDemoTimer()  { demoTimer->pause(); }
void DemoArea::resumeDemoTimer() { demoTimer->resume(); }

void DemoArea::advanceDemo() {
    if (demoSchedule.empty()) return;
    size_t next = (demoIndex.load(std::memory_order_relaxed) + 1) % demoSchedule.size();
    demoIndex.store(next, std::memory_order_relaxed);
}

void DemoArea::setHandsOnAllowed(bool allowed) {
    std::lock_guard<std::mutex> lock(stateMutex);
    if (isOpen && equipmentReady) {
        handsOnAllowed = allowed;
    } else {
        handsOnAllowed = false;
    }
}

bool DemoArea::isHandsOnAllowed() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return handsOnAllowed;
}

bool DemoArea::isEquipmentReady() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return equipmentReady;
}

std::string DemoArea::getCurrentDemo() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    if (isOpen && !demoSchedule.empty()) {
        return demoSchedule[demoIndex.load(std::memory_order_relaxed)];
    }
    return "Area is closed. No demonstration active.";
}

std::string DemoArea::getDemoDetails() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    if (isOpen && !demoSpecs.empty()) {
        size_t idx = demoIndex.load(std::memory_order_relaxed);
        if (idx < demoSpecs.size()) {
            return demoSpecs[idx];
        }
    }
    return "No active demo specs available.";
}

std::string DemoArea::getStatus() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return "- " + getName() + ": " + status + " [Visitors: " + 
           std::to_string(currentVisitors) + "/" + std::to_string(capacity) + "]\n";
}