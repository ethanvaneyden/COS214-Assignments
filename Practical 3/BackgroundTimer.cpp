#include "BackgroundTimer.h"

BackgroundTimer::BackgroundTimer() : running(false) {}

BackgroundTimer::~BackgroundTimer() {
    stop();
}

void BackgroundTimer::start(std::chrono::milliseconds interval, std::function<void()> task) {
        stop(); // Ensure any previous worker is stopped
        running = true;
        worker = std::thread([this, interval, task]() {
            std::unique_lock<std::mutex> lock(mutex);
            while (running) {
                // Wait for interval OR stop signal (prevents delay when shutting down)
                if (cv.wait_for(lock, interval, [this] { return !running; })) {
                    break; // stop() was called
                }
                // Perform the scheduled task
                task();
            }
        });
}

void BackgroundTimer::stop() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (!running) return;
            running = false;
        }
        cv.notify_one();
        if (worker.joinable()) {
            worker.join();
        }
}