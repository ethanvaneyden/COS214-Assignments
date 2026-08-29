#include "BackgroundTimer.h"

void StoppedState::start(BackgroundTimer& context, std::chrono::milliseconds interval, std::function<void()> task) {
    context.activeInterval = interval;
    context.activeTask = task;

    context.transitionTo(std::unique_ptr<TimerState>(new RunningState()));

    context.worker = std::thread([&context]() {
        std::unique_lock<std::mutex> lock(context.cvMutex);
        while (context.isRunning()) {

            if (context.isPaused()) {
                // Wait indefinitely until resumed or stopped
                context.cv.wait(lock, [&context]() {
                    return !context.isPaused() || !context.isRunning();
                });
                continue;
            }

            // Sleep for 'interval' OR wake early on state transition
            bool wokenEarly = context.cv.wait_for(lock, context.activeInterval, [&context]() {
                return !context.isRunning() || context.isPaused();
            });

            // Execute task only if still running naturally when interval expires
            if (!wokenEarly && context.isRunning() && !context.isPaused()) {
                if (context.activeTask) {
                    context.activeTask();
                }
            }
        }
    });
}

void RunningState::pause(BackgroundTimer& context) {
    context.transitionTo(std::unique_ptr<TimerState>(new PausedState()));
    context.cv.notify_one();
}

void RunningState::stop(BackgroundTimer& context) {
    context.transitionTo(std::unique_ptr<TimerState>(new StoppedState()));
    context.cv.notify_one();
    if (context.worker.joinable()) {
        context.worker.join();
    }
}

void PausedState::resume(BackgroundTimer& context) {
    context.transitionTo(std::unique_ptr<TimerState>(new RunningState()));
    context.cv.notify_one();
}

void PausedState::stop(BackgroundTimer& context) {
    context.transitionTo(std::unique_ptr<TimerState>(new StoppedState()));
    context.cv.notify_one();
    if (context.worker.joinable()) {
        context.worker.join();
    }
}

/**
    Abstract class implementation
*/
BackgroundTimer::BackgroundTimer() {
    state = std::unique_ptr<TimerState>(new StoppedState());
}

BackgroundTimer::~BackgroundTimer() {
    stop();
}

void BackgroundTimer::transitionTo(std::unique_ptr<TimerState> newState)
{
    // State transitions are already performed while stateMutex is held.
    state = std::move(newState);
}

void BackgroundTimer::start(std::chrono::milliseconds interval, std::function<void()> task) {
    stop(); // Ensure any existing thread is joined safely first
    std::lock_guard<std::mutex> lock(stateMutex);
    state->start(*this, interval, task);
}

void BackgroundTimer::pause() {
    std::lock_guard<std::mutex> lock(stateMutex);
    state->pause(*this);
}

void BackgroundTimer::resume() {
    std::lock_guard<std::mutex> lock(stateMutex);
    state->resume(*this);
}

void BackgroundTimer::stop() {
    std::lock_guard<std::mutex> lock(stateMutex);
    state->stop(*this);
}

bool BackgroundTimer::isRunning() const {
    return state->isRunning();
}

bool BackgroundTimer::isPaused() const {
    return state->isPaused();
}