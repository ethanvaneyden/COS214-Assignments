#ifndef MAINSTAGE_H
#define MAINSTAGE_H

#include <atomic>
#include <chrono>
#include <string>
#include <vector>

#include "SignalSubscriber.h"
#include "TechSignal.h"
class BackgroundTimer;
class Technician;

class MainStage : public SignalSubscriber {
public:
    MainStage();

    void startStaffTimer();
    void stopStaffTimer();
    void advanceStaff();

    std::string getStaff() const;
    
    virtual void update(const TechSignal &signal);
    virtual void add(SignalSubscriber* subscriber);

    ~MainStage() override = default;

private:
    std::vector<SignalSubscriber*> subscribers;
    std::vector<Technician> staff;
    std::atomic<size_t> staffIndex;
    BackgroundTimer staffTimer;
    std::chrono::minutes staffInterval;
};

#endif