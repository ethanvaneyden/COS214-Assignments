#ifndef AIDEMOBOOTH_H
#define AIDEMOBOOTH_H

#include "EventLeaf.h"
#include "TechSignal.h"
#include <iostream>
#include <string>

class AIDemoBooth : public EventLeaf {
private:
    bool isOpen;
    bool active;
    int capacity;
    int currentVisitors;
    bool requiresNetwork;
    bool demoRunning;
    std::string status;

public:
    explicit AIDemoBooth(EventComponent *parent = nullptr);
    ~AIDemoBooth() override = default;

    void update(const TechSignal &signal) override;
    void open() override;
    void close() override;

    std::string getStatus() const override;

    int getCapacity() const override;
    int getCurrentVisitors() const override;
    int enterVisitor(int visitors) override;
    int leaveVisitor(int visitors) override;
};

#endif // AIDEMOBOOTH_H