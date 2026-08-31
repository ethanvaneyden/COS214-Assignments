#ifndef ROBOTICSBOOTH_H
#define ROBOTICSBOOTH_H

#include "EventLeaf.h"
#include "TechSignal.h"
#include <iostream>
#include <string>

class RoboticsBooth : public EventLeaf {
private:
    bool isOpen;
    bool active;
    bool safeMode;
    int capacity;
    int currentVisitors;
    bool robotsActive;
    std::string lastMessage;

public:
    explicit RoboticsBooth(EventComponent *parent = nullptr);
    ~RoboticsBooth() override = default;

    void update(const TechSignal &signal) override;
    void open() override;
    void close() override;

    std::string getStatus() const override;

    int getCapacity() const override;
    int getCurrentVisitors() const override;
    int enterVisitor(int visitors) override;
    int leaveVisitor(int visitors) override;
};

#endif // ROBOTICSBOOTH_H