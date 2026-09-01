#ifndef AIZONE_H
#define AIZONE_H

#include "EventComposite.h"
#include "SignalBroadcaster.h"
#include "TechSignal.h"
#include <iostream>
#include <string>

class AIZone : public EventComposite {
private:
    bool isOpen;
    
public:
    explicit AIZone(EventComponent* parent);
    ~AIZone() override = default;

    void add(EventComponent* component) override;
    void remove(EventComponent* component) override;

    void open() override;
    void close() override;

    std::string getStatus() const override;
    
    int getCapacity() const override;
    int getCurrentVisitors() const override;
    void update(const TechSignal& signal) override;

    int enterVisitor(int visitors) override;
    int leaveVisitor(int visitors) override;
};

#endif // AIZONE_H