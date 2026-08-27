#ifndef KEYNOTEAREA_H
#define KEYNOTEAREA_H

#include "SignalSubscriber.h"
class Technician;

class KeyNoteArea : public SignalSubscriber {
public:
    explicit KeyNoteArea(
        const std::vector<std::string>& presenters = {
            "Satoshi Nakamoto", "Marti Stair", "Zink Weiss",
            "Fiorello Rocco", "Lorato Ramatlapeng"
        },
        const std::vector<Technician>& onDuty = {
            Technician("Stephen Groos", "082 555 1234"),
            Technician("John MacMillan", "084 742 9051"),
            Technician("Njabulo Sishebo", "083 123 4567"),
            Technician("Moaltegi Tlhabane", "083 987 6543"),
            Technician("Anthoni van Nordy", "082 111 2222"),
            Technician("Montechristo Delgado", "084 555 6666")
        },
        std::chrono::minutes presenterInterval = std::chrono::minutes(2),
        std::chrono::minutes onDutyInterval = std::chrono::minutes(5)
    );

    void update(const TechSignal &signal) override;

    ~KeyNoteArea() override = default;
};

#endif