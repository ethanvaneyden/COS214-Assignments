/**
 * @file BackgroundTimer.h
 * @brief Thread-safe background timer
 */

#ifndef BACKGROUNDTIMER_H
#define BACKGROUNDTIMER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>
#include <functional>

class BackgroundTimer;

/**
 * @brief Abstract base class for BackgroundTimer states.
 */
class TimerState {
public:
    virtual ~TimerState() = default;
    virtual void start(BackgroundTimer& context, std::chrono::milliseconds interval, std::function<void()> task) {}
    virtual void pause(BackgroundTimer& context) {}
    virtual void resume(BackgroundTimer& context) {}
    virtual void stop(BackgroundTimer& context) {}
    virtual bool isRunning() const { return false; }
    virtual bool isPaused() const { return false; }
};

/**
 * @brief Represents the stopped state of the timer.
 */
class StoppedState : public TimerState {
public:
    void start(BackgroundTimer& context, std::chrono::milliseconds interval, std::function<void()> task) override;
};

/**
 * @brief Represents the actively running state of the timer.
 */
class RunningState : public TimerState {
public:
    void pause(BackgroundTimer& context) override;
    void stop(BackgroundTimer& context) override;
    bool isRunning() const override { return true; }
};

/**
 * @brief Represents the paused state of the timer.
 */
class PausedState : public TimerState {
public:
    void resume(BackgroundTimer& context) override;
    void stop(BackgroundTimer& context) override;
    bool isRunning() const override { return true; }
    bool isPaused() const override { return true; }
};

/**
 * @class BackgroundTimer
 * @brief Manages a background thread timer using an internal State Machine.
 */
class BackgroundTimer {
public:
    BackgroundTimer();
    ~BackgroundTimer();

    void start(std::chrono::milliseconds interval, std::function<void()> task);
    void pause();
    void resume();
    void stop();

    bool isRunning() const;
    bool isPaused() const;

    void transitionTo(std::unique_ptr<TimerState> newState);

private:
    friend class StoppedState;
    friend class RunningState;
    friend class PausedState;

    std::unique_ptr<TimerState> state;
    std::mutex stateMutex;
    std::mutex cvMutex;
    std::condition_variable cv;
    std::thread worker;

    std::chrono::milliseconds activeInterval{0};
    std::function<void()> activeTask;
};

#endif /* BACKGROUNDTIMER_H */