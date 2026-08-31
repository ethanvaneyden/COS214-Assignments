#ifndef BYTESIZEDBIES_H
#define BYTESIZEDBIES_H

#include "SignalSubscriber.h"
#include "EventComponent.h"
#include "EventLeaf.h"
#include "TechSignal.h"

#include <iostream>
#include <unordered_map>

class ByteSizedBites : public EventLeaf {
    private:
        bool isOpen;
        int TotalChairs;
        int visitorOnChairs;

        //drinks(cokes and juice...) , food, snacks, energyBars, sandwhich

    public:
        explicit ByteSizedBites();

        void update(const TechSignal& signal) override;

        void open() override;

        void close() override;

        std::string getStatus() const override;

        int getCapacity() const override; //int TotalChairs and int visitorsOnChairs;

        ~ByteSizedBites() override = default;
};

#endif
