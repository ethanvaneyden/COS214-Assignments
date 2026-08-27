#ifndef KEYNOTEAREA_H
#define KEYNOTEAREA_H

#include <vector>
#include <atomic>
#include <string>
#include <chrono>

#include "SignalSubscriber.h"

class BackgroundTimer;

class KeyNoteArea : public SignalSubscriber {
public:
    explicit KeyNoteArea();
    void update(const TechSignal &signal) override;

    void startPresenterTimer();
    void stopPresenterTimer();
    void pausePresenterTimer();
    void resumePresenterTime();
    void advancePresenter();

    std::string getPresenter() const;
    std::string getStatus() const;
    
    ~KeyNoteArea() override = default;
private:
    bool isOpen;
    std::string status;

    std::vector<std::string> presenters;
    std::atomic<size_t> presenterIndex;
    BackgroundTimer presenterTimer;
    std::chrono::minutes presenterInterval;
};

#endif