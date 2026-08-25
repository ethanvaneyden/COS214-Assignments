#ifndef SIGNALSUBSCRIBER_H
#define SIGNALSUBSCRIBER_H

#include "BackgroundTimer.h"
#include "Technician.h"
#include "TechSignal.h"
#include <vector>
#include <string>
#include <atomic>
#include <chrono>

class SignalSubscriber {
public:
    SignalSubscriber(
        std::string name,
        std::vector<std::string> presenters,
        std::vector<Technician> onDuty,
        std::chrono::minutes presenterInterval,
        std::chrono::minutes onDutyInterval
    );
    virtual ~SignalSubscriber() = default;

    virtual void startTimers();
    virtual void stopTimers();
    virtual void pausePresenting();
    virtual void resumePresenting();

    void advancePresenter();
    void advanceOnDuty();

    std::string getPresenter() const;
    std::string getOnDuty() const;
    std::string getStatus() const;

    virtual void update(const TechSignal& signal) = 0;

protected:
    std::string areaName;
    bool isOpen{true};
    std::string status;

    std::vector<std::string> presenters;
    std::vector<Technician> onDuty;

    std::atomic<size_t> presenterIndex{0};
    std::atomic<size_t> onDutyIndex{0};

    BackgroundTimer presenterTimer;
    BackgroundTimer onDutyTimer;

    std::chrono::minutes presenterInterval;
    std::chrono::minutes onDutyInterval;
};

#endif