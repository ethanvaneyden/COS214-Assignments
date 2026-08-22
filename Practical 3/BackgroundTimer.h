#ifndef BACKGROUNDTIMER_H
#define BACKGROUNDTIMER_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <functional>


/**
 * @class BackgroundTimer
 * @brief Executes a user-defined task periodically in a dedicated background thread.
 * 
 * Uses a condition variable to efficiently sleep between intervals without burning CPU cycles
 * and allows for an immediate stop/shutdown without waiting for active sleep intervals to expire.
 */
class BackgroundTimer {
public:
    /**
     * @brief Constructs an idle BackgroundTimer instance.
     */
    BackgroundTimer();

    /**
     * @brief Destructor. Automatically calls stop() to safely terminate the background thread.
     */
    ~BackgroundTimer();

    /**
     * @brief Starts executing a task periodically at a specified interval.
     * 
     * If a worker thread is already running, it is stopped before the new task is started.
     * 
     * @param interval Duration to wait between successive task executions.
     * @param task Callable object (lambda, function pointer, or std::function) to run.
     */
    void start(std::chrono::milliseconds interval, std::function<void()> task);

    /**
     * @brief Stops the background worker thread if running.
     * 
     * Signals the worker thread to exit immediately and joins it. Safe to call multiple times.
     */
    void stop();

private:
    std::atomic<bool> running;  /** Flag indicating if the background thread is active. */
    std::mutex mutex;           /** Mutex protecting internal cv wait condition state. */
    std::condition_variable cv; /** Condition variable used for interruptible interval sleeps. */
    std::thread worker;         /** Worker thread handle. */
};


#endif /* BACKGROUNDTIMER_H */