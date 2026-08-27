#ifndef MAINSTAGE_H
#define MAINSTAGE_H

#include <vector>
#include <atomic>
#include <string>
#include <chrono>

#include "SignalSubscriber.h"


class Technician;

class MainStage : public SignalSubscriber {
public:
    explicit MainStage();

    void startStaffTimer();
    void stopStaffTimer();
    void advanceStaff();
    std::string getStaff() const;

    ~MainStage() override = default;

private:
    std::vector<Technician> staff;
    std::atomic<size_t> staffIndex;
    BackgroundTimer staffTimer;
    std::chrono::minutes staffInterval;
};



#endif
