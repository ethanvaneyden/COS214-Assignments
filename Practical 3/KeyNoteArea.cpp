#include "KeyNoteArea.h"
#include "BackgroundTimer.h"
#include "EventComponent.h"
#include "TechSignal.h"

using namespace std::chrono;

KeyNoteArea::KeyNoteArea(EventComponent *parent)
    : EventLeaf("Keynote area", parent), isOpen(true), presenterIndex(0),
      presenterInterval(minutes(2)), presenterTimer(new BackgroundTimer()) {
  presenters = {"Satoshi Nakamoto", "Marti Stair", "Zink Weiss",
                "Fiorello Rocco", "Lorato Ramatlapeng"};
}

KeyNoteArea::~KeyNoteArea() { delete presenterTimer; }

void KeyNoteArea::update(const TechSignal &signal) {
  std::lock_guard<std::mutex> lock(stateMutex);

  switch (signal.getType()) {
  case TechSignal::Type::UNKNOWN:
    status = "Unknown signal received.";
    break;
  case TechSignal::Type::OPEN:
    status = "Key Note Area is now open.";
    isOpen = true;
    if (presenterTimer->isPaused()) {
      resumePresenterTimer();
    } else if (!presenterTimer->isRunning()) {
      startPresenterTimer();
    }
    break;
  case TechSignal::Type::CLOSE:
    status = "Key Note Area is now closed.";
    isOpen = false;
    stopPresenterTimer();
    break;
  case TechSignal::Type::FULL_CAPACITY:
    status = "Key Note Area has reached full capacity.";
    break;
  case TechSignal::Type::SCHEDULE_CHANGE:
    status = "Schedule change in Key Note Area.\n Please contact the "
             "technician on duty: " +
             getStaff();
    break;
  case TechSignal::Type::POWER_FAILURE:
    status = "Power failure in Key Note Area.\n Please contact the technician "
             "on duty: " +
             getStaff();
    isOpen = false;
    pausePresenterTimer();
    break;
  case TechSignal::Type::EMERGENCY_PAUSE:
    status = "Emergency pause in Key Note Area.\n Please contact the "
             "technician on duty: " +
             getStaff();
    pausePresenterTimer();
    break;
  default:
    break;
  }
}

void KeyNoteArea::startPresenterTimer() {
  presenterTimer->start(presenterInterval, [this]() { advancePresenter(); });
  if (!isOpen) {
    pausePresenterTimer();
  }
}

void KeyNoteArea::stopPresenterTimer() { presenterTimer->stop(); }
void KeyNoteArea::pausePresenterTimer() { presenterTimer->pause(); }
void KeyNoteArea::resumePresenterTimer() { presenterTimer->resume(); }

void KeyNoteArea::advancePresenter() {
  if (presenters.empty())
    return;
  size_t next =
      (presenterIndex.load(std::memory_order_relaxed) + 1) % presenters.size();
  presenterIndex.store(next, std::memory_order_relaxed);
}

std::string KeyNoteArea::getPresenter() const {
  std::lock_guard<std::mutex> lock(stateMutex);
  if (isOpen && !presenters.empty()) {
    return presenters[presenterIndex.load(std::memory_order_relaxed)];
  }
  return "Area is closed. No presenter available.";
}

std::string KeyNoteArea::getStatus() const {
  std::lock_guard<std::mutex> lock(stateMutex);
  return "- Key Note Area: " + status + "\n";
}