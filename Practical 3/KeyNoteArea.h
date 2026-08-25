#ifndef KEYNOTEAREA_H
#define KEYNOTEAREA_H

#include "SignalSubscriber.h"
#include <vector>
#include <string>
#include <atomic>

class BackgroundTimer;
class Technician;

class KeyNoteArea : public SignalSubscriber {
public:
    explicit KeyNoteArea(std::string name);
    void startTimers();
    void stopTimers();
    void pausePresenting();
    void resumePresenting();

    void advancePresenter();
    void advanceOnDuty();

    std::string getPresenter() const;
    std::string getOnDuty() const;

    void update(const TechSignal &signal);

    ~KeyNoteArea() = default;
private:
    std::string areaName;
    bool isOpen;
    std::string status;

    std::vector<std::string> presenters;
    std::vector<Technician> onDuty;

    std::atomic<size_t> presenterIndex;
    std::atomic<size_t> onDutyIndex;

    BackgroundTimer presenterTimer;
    BackgroundTimer onDutyTimer;
};

#endif /* KEYNOTEAREA_H */