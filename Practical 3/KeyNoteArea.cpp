#include "KeyNoteArea.h"
#include "BackgroundTimer.h"
#include "EventComponent.h"
#include "TechSignal.h"
#include <iostream>
#include <sstream>

using namespace std::chrono;

KeyNoteArea::KeyNoteArea(EventComponent *parent)
    : EventLeaf("Keynote_Area", parent),
      isOpen(true),
      presenterIndex(0),
      presenterInterval(minutes(2)),
      presenterTimer(new BackgroundTimer()) 
{

    presenters = {
        "Satoshi Nakamoto",
        "Marti Stair",
        "Zink Weiss",
        "Fiorello Rocco",
        "Lorato Ramatlapeng"
    };
}

KeyNoteArea::~KeyNoteArea(){
    delete presenterTimer;
}

std::string KeyNoteArea::getStatus() const {
    std::stringstream ss;
    ss << "- KeyNote Area: " << (isOpen ? "OPEN" : "CLOSED")
       << " | Presenter: " << getPresenter() << "\n";
    return ss.str();
}

void KeyNoteArea::update(const TechSignal &signal){

    std::lock_guard<std::mutex> lock(stateMutex);

    switch(signal.getType()){

    case TechSignal::Type::UNKNOWN:
        status = "Unknown signal received.";
        break;

    case TechSignal::Type::OPEN:
        status = "Key Note Area is now open.";
        isOpen = true;

        /*
         * The timer is handled after the lock is released.
         * This prevents the timer functions from trying to use the
         * same mutex while it is still locked.
         */
        break;

    case TechSignal::Type::CLOSE:
        status = "Key Note Area is now closed.";
        isOpen = false;
        break;

    case TechSignal::Type::FULL_CAPACITY:
        status = "Key Note Area has reached full capacity.";
        break;

    case TechSignal::Type::SCHEDULE_CHANGE:
        status = "Schedule change in Key Note Area.\n"
                 "Please contact the technician on duty: " +
                 getStaff();
        break;

    case TechSignal::Type::POWER_FAILURE:
        status = "Power failure in Key Note Area.\n"
                 "Please contact the technician on duty: " +
                 getStaff();

        isOpen = false;
        break;

    case TechSignal::Type::EMERGENCY_PAUSE:
        status = "Emergency pause in Key Note Area.\n"
                 "Please contact the technician on duty: " +
                 getStaff();
        break;

    case TechSignal::Type::RESUME:
        status = "Key Note Area has resumed.";

        if(isOpen){
            status = "Key Note Area has resumed.";
        }
        break;

    default:
        break;
    }

    /*
     * Timer operations are done here after the lock is released.
     *
     * OPEN:
     * Start or resume the presenter timer.
     *
     * CLOSE:
     * Stop the presenter timer.
     *
     * POWER_FAILURE:
     * Pause the timer.
     *
     * EMERGENCY_PAUSE:
     * Pause the timer.
     *
     * RESUME:
     * Resume the timer.
     */
    switch(signal.getType()){

    case TechSignal::Type::OPEN:
        if(presenterTimer->isPaused()){
            resumePresenterTimer();
        }
        else if(!presenterTimer->isRunning()){
            startPresenterTimer();
        }
        break;

    case TechSignal::Type::CLOSE:
        stopPresenterTimer();
        break;

    case TechSignal::Type::POWER_FAILURE:
    case TechSignal::Type::EMERGENCY_PAUSE:
        pausePresenterTimer();
        break;

    case TechSignal::Type::RESUME:
        if(isOpen){
            resumePresenterTimer();
        }
        break;

    default:
        break;
    }
}

void KeyNoteArea::open(){

    /*
     * FIX:
     *
     * The old code did:
     *
     *     std::lock_guard<std::mutex> lock(stateMutex);
     *     ...
     *     lock.~lock_guard();
     *
     * Manually destroying the lock_guard is dangerous.
     *
     * Instead, we allow the lock_guard to leave its scope normally.
     */

   {
        std::lock_guard<std::mutex> lock(stateMutex);

        isOpen = true;
        status = "Key Note Area is now open.";
    }

    /*
     * The mutex has now been released.
     * It is safe to work with the timer.
     */
    if(presenterTimer->isPaused()){
        resumePresenterTimer();
    }
    else if(!presenterTimer->isRunning()){
        startPresenterTimer();
    }
}

void KeyNoteArea::close(){

   {
        std::lock_guard<std::mutex> lock(stateMutex);

        isOpen = false;
        status = "Key Note Area is now closed.";
    }

    /*
     * The mutex has been released before stopping the timer.
     */
    stopPresenterTimer();
}

int KeyNoteArea::getCapacity() const{
    return 0;
}

int KeyNoteArea::enterVisitor(int visitors){
    return visitors > 0 ? 0 : 0;
}

int KeyNoteArea::leaveVisitor(int visitors){
    return visitors > 0 ? 0 : 0;
}

int KeyNoteArea::getCurrentVisitors() const{
    return 0;
}

void KeyNoteArea::startPresenterTimer(){

    presenterTimer->start(
        presenterInterval,
        [this](){
            advancePresenter();
        }
    );

    if(!isOpen){
        pausePresenterTimer();
    }
}

void KeyNoteArea::stopPresenterTimer(){
    presenterTimer->stop();
}

void KeyNoteArea::pausePresenterTimer(){
    presenterTimer->pause();
}

void KeyNoteArea::resumePresenterTimer(){
    presenterTimer->resume();
}

void KeyNoteArea::advancePresenter(){

    if(presenters.empty()){
        return;
    }

    size_t next =
       (presenterIndex.load(std::memory_order_relaxed) + 1)
        % presenters.size();

    presenterIndex.store(
        next,
        std::memory_order_relaxed
    );
}

std::string KeyNoteArea::getPresenter() const{

    std::lock_guard<std::mutex> lock(stateMutex);

    if(isOpen && !presenters.empty()){
        return presenters[
            presenterIndex.load(std::memory_order_relaxed)
        ];
    }

    return "Area is closed. No presenter available.";
}
