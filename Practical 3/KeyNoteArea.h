#ifndef KEYNOTEAREA_H
#define KEYNOTEAREA_H

#include "SignalSubscriber.h"
#include <vector>
#include <string>
#include <atomic>


class BackgroundTimer;

class KeyNoteArea : public SignalSubscriber {
    explicit KeyNoteArea(std::string name);
    void startTimers();
    void stopTimers();

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

    const std::vector<std::string> presenters = {
        "Satoshi Nakamoto", "Marti Stair", "Zink Weiss",
        "Fiorello Rocco", "Lorato Ramatlapeng"
    };

    const std::vector<std::string> onDuty = {
        "Stephen Groos", "John MacMillan", "Njabulo Sishebo",
        "Moaltegi Tlhabane", "Anthoni van Nordy", "Montechristo Delgado"
    };

    std::atomic<size_t> presenterIndex;
    std::atomic<size_t> onDutyIndex;

    BackgroundTimer presenterTimer;
    BackgroundTimer onDutyTimer;
};

#endif /* KEYNOTEAREA_H */