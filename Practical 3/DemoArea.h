#ifndef DEMOAREA_H
#define DEMOAREA_H

#include "SignalSubscriber.h"
class Technician;

class DemoArea : public SignalSubcriber {
public:
    explicit DemoArea(
        const std::vector<std::string>& presenters = {
            "GS Labs", "Omikron", "Chronus"
        },
        const std::vector<Technician>& onDuty = {
            Technician("Onthatile Molelekeng", "074 734 1820"),
            Technician("Clement Bach", "064 129 2789"),
            Technician("Tim Dry", "074 947 1947"),
            Technician("Nathan Lobby", "085 441 3255")
        }
    )
};

#endif