#include "MainStage.h"
#include "Technician.h"
#include "BackgroundTimer.h"

MainStage::MainStage()
{
    staff = {
        Technician("Stephen Groos", "082 555 1234"),
        Technician("John MacMillan", "084 742 9051"),
        Technician("Njabulo Sishebo", "083 123 4567"),
        Technician("Moaltegi Tlhabane", "083 987 6543"),
        Technician("Anthoni van Nordy", "082 111 2222"),
        Technician("Montechristo Delgado", "084 555 6666")};
    staffInterval = std::chrono::minutes(5);
    staffIndex = 0;
}

void MainStage::startStaffTimer()
{
    staffTimer.start(staffInterval, [this]()
                     { advanceStaff(); });
}

void MainStage::stopStaffTimer()
{
    staffTimer.stop();
}

void MainStage::advanceStaff()
{
    if (staff.empty())
        return;
    size_t next = (staffIndex.load(std::memory_order_relaxed) + 1) % staff.size();
    staffIndex.store(next, std::memory_order_relaxed);
}

std::string MainStage::getStaff() const
{
    if (staff.empty())
        return "No technician on duty.";
    return staff[staffIndex.load(std::memory_order_relaxed)];
}

void MainStage::update(const TechSignal &signal)
{
    for (SignalSubscriber *sub : subscribers)
        sub->update(signal);
}

void MainStage::add(SignalSubscriber *subscriber)
{
    subscribers.push_back(subscriber);
}
