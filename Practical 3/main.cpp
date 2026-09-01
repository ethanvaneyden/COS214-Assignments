#include <atomic>
#include <cassert>
#include <chrono>
#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <thread>

#include "AIDemoBooth.h"
#include "AIZone.h"
#include "BackgroundTimer.h"
#include "ByteSizedBites.h"
#include "DemoArea.h"
#include "EventComponent.h"
#include "ExpoRegistry.h"
#include "KeyNoteArea.h"
#include "MainStage.h"
#include "MapBuilder.h"
#include "RoboticsBooth.h"
#include "SignalBroadcaster.h"
#include "SignalSubscriber.h"
#include "Technician.h"
#include "TechSignal.h"

void printHelp();
void runGame();

namespace {

    class RecordingSubscriber : public SignalSubscriber {
        public:
            RecordingSubscriber() : notifications(0), lastType(TechSignal::Type::UNKNOWN){}

            void update(const TechSignal& signal) override{
                ++notifications;
                lastType = signal.getType();
            }

            int notifications;
            TechSignal::Type lastType;
    };

    void heading(const char* text){
        std::cout << "\n====================================================\n"
                << text << "\n"
                << "====================================================\n";
    }

    void testTechSignals(){
        heading("1. TechSignal constructors and getters");

        TechSignal byText("open", "low", "Open for visitors");
        TechSignal inferred("power_failure", "Power supply interrupted");
        TechSignal byEnums(TechSignal::Type::EMERGENCY_PAUSE,
                        TechSignal::Priority::CRITICAL,
                        "Safety officer requested a pause");
        TechSignal inferredEnum(TechSignal::Type::FULL_CAPACITY,
                                "Capacity limit reached");
        TechSignal unknown("not_a_real_signal", "unknown", "Negative test");

        assert(byText.getType() == TechSignal::Type::OPEN);
        assert(byText.getPriority() == TechSignal::Priority::LOW);
        assert(inferred.getPriority() == TechSignal::Priority::HIGH);
        assert(byEnums.getMessage() == "Safety officer requested a pause");
        assert(inferredEnum.getPriority() == TechSignal::Priority::MEDIUM);
        assert(unknown.getType() == TechSignal::Type::UNKNOWN);
    }

    void testObserver(){
        heading("2. SignalBroadcaster registration");

        SignalBroadcaster broadcaster;
        RecordingSubscriber first;
        RecordingSubscriber second;
        TechSignal notice("change_schedule", "The keynote begins at 11:00.");

        broadcaster.subscribe(nullptr);
        broadcaster.subscribe(&first);
        broadcaster.subscribe(&first);
        broadcaster.subscribe(&second);
        assert(broadcaster.getSubscriberCount() == 2);

        broadcaster.transmit(notice);
        assert(first.notifications == 1);
        assert(second.notifications == 1);
        assert(first.lastType == TechSignal::Type::SCHEDULE_CHANGE);

        broadcaster.unsubscribe(&first);
        broadcaster.unsubscribe(&first);
        assert(broadcaster.getSubscriberCount() == 1);
        broadcaster.transmit(TechSignal("close", "Detach check"));
        assert(first.notifications == 1);
        assert(second.notifications == 2);

        broadcaster.clearSubscribers();
        assert(broadcaster.getSubscriberCount() == 0);
    }

    void testTimer(){
        heading("3. BackgroundTimer states");

        std::atomic<int> ticks(0);
        BackgroundTimer timer;
        timer.start(std::chrono::milliseconds(10), [&ticks](){ ++ticks; });
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        assert(timer.isRunning());

        timer.pause();
        assert(timer.isRunning());
        assert(timer.isPaused());

        timer.resume();
        assert(timer.isRunning());
        assert(!timer.isPaused());

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        timer.stop();
        assert(!timer.isRunning());
        assert(ticks.load() > 0);
    }

    void testStandaloneLeaves(){
        heading("4. AI, robotics and food leaves");

        AIDemoBooth ai(2, "AI_Demo_Booth");
        RoboticsBooth robotics(3, "Robotics_Booth");
        ByteSizedBites food("ByteSizedBites");

        ai.open();
        assert(ai.enterVisitor(1) == 1);
        assert(ai.enterVisitor(5) == 1);
        assert(ai.getCurrentVisitors() == 2);
        assert(ai.leaveVisitor(5) == 2);
        assert(ai.enterVisitor(0) == 0);
        ai.update(TechSignal("network_failure", "Network maintenance"));
        ai.update(TechSignal("power_failure", "Power interruption"));
        ai.update(TechSignal("resume", "Power restored"));
        ai.update(TechSignal("emergency_pause", "Safety drill"));
        ai.update(TechSignal("change_schedule", "Demo starts later"));
        ai.reportStatus();

        robotics.open();
        assert(robotics.enterVisitor(2) == 2);
        assert(robotics.enterVisitor(5) == 1);
        assert(robotics.getCurrentVisitors() == 3);
        assert(robotics.leaveVisitor(5) == 3);
        assert(robotics.leaveVisitor(0) == 0);
        robotics.update(TechSignal("power_failure", "Power interruption"));
        robotics.update(TechSignal("resume", "Power restored"));
        robotics.update(TechSignal("emergency_pause", "Safety drill"));
        robotics.update(TechSignal("change_schedule", "Showcase moved"));
        robotics.reportStatus();

        assert(!food.getIsOpen());
        food.open();
        assert(food.getIsOpen());
        food.setTotalChairs(4);
        food.setTotalChairs(-1);
        assert(food.getTotalChairs() == 4);
        assert(food.enterVisitor(5) == 4);
        assert(food.getCurrentVisitors() == 4);
        assert(food.leaveVisitor(2) == 2);
        food.setVisitorsOnChairs(4);
        food.setVisitorsOnChairs(10);
        assert(food.getVisitorsOnChairs() == 4);
        assert(food.removeVisitor());

        food.setFoodStock(10);
        food.setDrinkStock(10);
        food.setSnackStock(10);
        food.setEnergyBarStock(10);
        assert(food.useFood(2));
        assert(food.useDrink(2));
        assert(food.useSnack(2));
        assert(food.useEnergyBar(2));
        assert(!food.useFood(20));
        assert(!food.useDrink(0));
        assert(!food.useSnack(-1));
        assert(!food.useEnergyBar(20));

        food.setStaffCount(0);
        food.startOrder();
        assert(food.getOrdersInProgress() == 0);
        food.setStaffCount(2);
        food.startOrder();
        food.completeOrder();
        food.completeOrder();
        food.setSpecialOfTheDay("Binary Burger");
        assert(food.getSpecialOfTheDay() == "Binary Burger");
        food.update(TechSignal("full_capacity", "All chairs occupied"));
        food.update(TechSignal("network_failure", "Card system offline"));
        food.update(TechSignal("emergency_pause", "Safety drill"));
        food.update(TechSignal("resume", "Safety drill complete"));
        food.reportStatus();
    }

    void testAIZone(){
        heading("5. AIZone composite");

        AIZone zone("AI_Zone");
        AIDemoBooth ai(2, "Zone_AI_Booth");
        RoboticsBooth robotics(3, "Zone_Robotics_Booth");

        zone.add(nullptr);
        zone.add(&ai);
        zone.add(&ai);
        zone.add(&robotics);
        assert(zone.hasChildren());
        assert(zone.getCapacity() == 5);
        zone.open();
        assert(zone.enterVisitor(6) == 5);
        assert(zone.getCurrentVisitors() == 5);
        assert(zone.leaveVisitor(10) == 5);
        zone.update(TechSignal("network_failure", "Wireless maintenance"));
        zone.update(TechSignal("emergency_pause", "Safety drill"));
        zone.update(TechSignal("resume", "Safety drill complete"));
        zone.reportStatus();

        zone.remove(&ai);
        zone.remove(&ai);
        assert(ai.getParent() == nullptr);
        assert(zone.getCapacity() == 3);
    }

    void testRegistryFactoryAndRemoval(){
        heading("6. ExpoRegistry factory and removal");

        ExpoRegistry registry;
        EventComponent* hall = registry.createComponent(
            ExpoRegistry::ComponentType::EXHIBITION_HALL, nullptr);
        EventComponent* stage = registry.createComponent(
            ExpoRegistry::ComponentType::MAIN_STAGE, hall);
        EventComponent* keynote = registry.createComponent(
            ExpoRegistry::ComponentType::KEYNOTE_AREA, stage);
        EventComponent* demo = registry.createComponent(
            ExpoRegistry::ComponentType::DEMO_AREA, stage);

        assert(hall != nullptr && stage != nullptr && keynote != nullptr && demo != nullptr);
        assert(registry.findComponent("does_not_exist") == nullptr);
        assert(!registry.removeComponent("does_not_exist"));
        assert(!registry.removeComponent("Main_Stage"));
        assert(registry.removeComponent("Demo_Area"));
        assert(registry.removeComponent("Keynote_Area"));
        assert(registry.removeComponent("Main_Stage"));
        assert(registry.removeComponent("Main_Exhibition_Hall"));
    }

    void testEventScenario(){
        heading("7. EventFlow static demonstration");

        ExpoRegistry registry;
        MapBuilder builder;
        builder.build(registry);

        EventComponent* hall = registry.findComponent("Main_Exhibition_Hall");
        EventComponent* stage = registry.findComponent("Main_Stage");
        EventComponent* keynote = registry.findComponent("Keynote_Area");
        EventComponent* demo = registry.findComponent("Demo_Area");
        MainStage* mainStage = dynamic_cast<MainStage*>(stage);
        KeyNoteArea* keynoteArea = dynamic_cast<KeyNoteArea*>(keynote);
        DemoArea* demoArea = dynamic_cast<DemoArea*>(demo);
        assert(hall != nullptr && stage != nullptr && keynote != nullptr && demo != nullptr);
        assert(mainStage != nullptr && keynoteArea != nullptr && demoArea != nullptr);
        assert(stage->getParent() == hall);
        assert(keynote->getParent() == stage);
        assert(demo->getParent() == stage);

        registry.printMap();
        hall->open();
        assert(!mainStage->getStaff().empty());
        mainStage->advanceStaff();
        mainStage->reportStatus();
        assert(!keynoteArea->getPresenter().empty());
        keynoteArea->advancePresenter();
        keynoteArea->pausePresenterTimer();
        keynoteArea->resumePresenterTimer();
        keynoteArea->reportStatus();
        assert(!demoArea->getCurrentDemo().empty());
        assert(!demoArea->getDemoDetails().empty());
        demoArea->setHandsOnAllowed(true);
        assert(demoArea->isHandsOnAllowed());
        assert(demoArea->isEquipmentReady());
        demoArea->advanceDemo();
        demoArea->pauseDemoTimer();
        demoArea->resumeDemoTimer();
        demoArea->reportStatus();
        assert(hall->getCapacity() == 100);
        assert(registry.enterVisitors("Demo_Area", -1) == 0);
        assert(registry.enterVisitors("Demo_Area", 40) == 40);
        assert(registry.enterVisitors("Demo_Area", 1000) == 60);
        assert(demo->getCurrentVisitors() == 100);
        assert(registry.leaveVisitors("Demo_Area", 25) == 25);
        assert(demo->getCurrentVisitors() == 75);
        registry.printCapacity("Demo_Area");
        registry.printCapacity("missing_component");

        assert(registry.transmitSignal(
            "Main_Exhibition_Hall",
            TechSignal("change_schedule", "Demo schedule moved to Hall B.")));
        assert(registry.transmitSignal(
            "Main_Exhibition_Hall",
            TechSignal("emergency_pause", "Please pause demonstrations.")));
        assert(registry.transmitSignal(
            "Main_Exhibition_Hall",
            TechSignal("resume", "Safety check complete.")));
        assert(!registry.transmitSignal("missing_component", TechSignal("open")));

        assert(registry.moveComponent("Demo_Area", "Main_Exhibition_Hall"));
        assert(demo->getParent() == hall);
        assert(registry.moveComponent("Demo_Area", "Main_Stage"));
        assert(demo->getParent() == stage);

        (*stage) >> (*stage);
        assert(stage->getParent() == hall);
        (*stage) >> (*demo);
        assert(stage->getParent() == hall);

        registry.printStatusReport();
        hall->close();
    }

    void testTechnician(){
        heading("8. Technician value object");

        Technician technician("Ace Lovelove", "012 345 6789");
        assert(technician.getName() == "Ace Lovelove");
        assert(technician.getContactInfo() == "012 345 6789");
        assert(static_cast<std::string>(technician) ==
            "Ace Lovelove (012 345 6789)");
    }

}

int main(){
    std::cout << "EventFlow static test harness\n";
    testTechSignals();
    testObserver();
    testTimer();
    testStandaloneLeaves();
    testAIZone();
    testRegistryFactoryAndRemoval();
    testEventScenario();
    testTechnician();
    //runGame(); interactive testing
    std::cout << "\nAll static tests completed successfully.\n";
    return 0;
}

void printHelp();
void runGame();

namespace
{

    class RecordingSubscriber : public SignalSubscriber
    {
    public:
        RecordingSubscriber() : notifications(0), lastType(TechSignal::Type::UNKNOWN) {}

        void update(const TechSignal &signal) override
        {
            ++notifications;
            lastType = signal.getType();
        }

        int notifications;
        TechSignal::Type lastType;
    };

    void heading(const char *text)
    {
        std::cout << "\n====================================================\n"
                  << text << "\n"
                  << "====================================================\n";
    }

    void testTechSignals()
    {
        heading("1. TechSignal constructors and getters");

        TechSignal byText("open", "low", "Open for visitors");
        TechSignal inferred("power_failure", "Power supply interrupted");
        TechSignal byEnums(TechSignal::Type::EMERGENCY_PAUSE,
                           TechSignal::Priority::CRITICAL,
                           "Safety officer requested a pause");
        TechSignal inferredEnum(TechSignal::Type::FULL_CAPACITY,
                                "Capacity limit reached");
        TechSignal unknown("not_a_real_signal", "invalid_priority", "Negative test");
        TechSignal fallbackSig("unknown", "invalid", "Fallback comparison");

        assert(byText.getType() == TechSignal::Type::OPEN);
        assert(byText.getPriority() == TechSignal::Priority::LOW);
        assert(inferred.getPriority() == TechSignal::Priority::HIGH);
        assert(byEnums.getMessage() == "Safety officer requested a pause");
        assert(inferredEnum.getPriority() == TechSignal::Priority::MEDIUM);
        assert(unknown.getType() == TechSignal::Type::UNKNOWN);
        assert(unknown.getPriority() == fallbackSig.getPriority());
    }

    void testObserver()
    {
        heading("2. SignalBroadcaster registration");

        SignalBroadcaster broadcaster;
        RecordingSubscriber first;
        RecordingSubscriber second;
        TechSignal notice("change_schedule", "The keynote begins at 11:00.");

        broadcaster.subscribe(nullptr);
        broadcaster.subscribe(&first);
        broadcaster.subscribe(&first);
        broadcaster.subscribe(&second);
        assert(broadcaster.getSubscriberCount() == 2);

        broadcaster.transmit(notice);
        assert(first.notifications == 1);
        assert(second.notifications == 1);
        assert(first.lastType == TechSignal::Type::SCHEDULE_CHANGE);

        broadcaster.unsubscribe(&first);
        broadcaster.unsubscribe(&first);
        assert(broadcaster.getSubscriberCount() == 1);
        broadcaster.transmit(TechSignal("close", "Detach check"));
        assert(first.notifications == 1);
        assert(second.notifications == 2);

        broadcaster.clearSubscribers();
        assert(broadcaster.getSubscriberCount() == 0);
    }

    void testTimer()
    {
        heading("3. BackgroundTimer states");

        std::atomic<int> ticks(0);
        BackgroundTimer timer;
        timer.start(std::chrono::milliseconds(10), [&ticks]()
                    { ++ticks; });
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        assert(timer.isRunning());

        timer.pause();
        assert(timer.isRunning());
        assert(timer.isPaused());

        timer.resume();
        assert(timer.isRunning());
        assert(!timer.isPaused());

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        timer.stop();
        assert(!timer.isRunning());
        assert(ticks.load() > 0);
    }

    void testStandaloneLeaves()
    {
        heading("4. AI, robotics and food leaves");

        AIDemoBooth ai(nullptr);
        RoboticsBooth robotics(nullptr);
        ByteSizedBites food(nullptr);

        ai.open();
        assert(ai.enterVisitor(1) == 1);
        assert(ai.enterVisitor(100) >= 0);
        assert(ai.leaveVisitor(100) >= 0);
        assert(ai.enterVisitor(0) == 0);
        ai.update(TechSignal("network_failure", "Network maintenance"));
        ai.update(TechSignal("power_failure", "Power interruption"));
        ai.update(TechSignal("resume", "Power restored"));
        ai.update(TechSignal("emergency_pause", "Safety drill"));
        ai.update(TechSignal("change_schedule", "Demo starts later"));
        std::cout << ai.getStatus();

        robotics.open();
        assert(robotics.enterVisitor(2) == 2);
        assert(robotics.enterVisitor(100) >= 0);
        assert(robotics.leaveVisitor(100) >= 0);
        assert(robotics.leaveVisitor(0) == 0);
        robotics.update(TechSignal("power_failure", "Power interruption"));
        robotics.update(TechSignal("resume", "Power restored"));
        robotics.update(TechSignal("emergency_pause", "Safety drill"));
        robotics.update(TechSignal("change_schedule", "Showcase moved"));
        std::cout << robotics.getStatus();

        assert(!food.getIsOpen());
        food.open();
        assert(food.getIsOpen());
        food.setTotalChairs(4);
        food.setTotalChairs(-1);
        assert(food.getTotalChairs() == 4);
        assert(food.enterVisitor(5) == 4);
        assert(food.getCurrentVisitors() == 4);
        assert(food.leaveVisitor(2) == 2);
        food.setVisitorsOnChairs(4);
        food.setVisitorsOnChairs(10);
        assert(food.getVisitorsOnChairs() == 4);
        assert(food.removeVisitor());

        food.setFoodStock(10);
        food.setDrinkStock(10);
        food.setSnackStock(10);
        food.setEnergyBarStock(10);
        assert(food.useFood(2));
        assert(food.useDrink(2));
        assert(food.useSnack(2));
        assert(food.useEnergyBar(2));
        assert(!food.useFood(20));
        assert(!food.useDrink(0));
        assert(!food.useSnack(-1));
        assert(!food.useEnergyBar(20));

        food.setStaffCount(0);
        food.startOrder();
        assert(food.getOrdersInProgress() == 0);
        food.setStaffCount(2);
        food.startOrder();
        food.completeOrder();
        food.completeOrder();
        food.setSpecialOfTheDay("Binary Burger");
        assert(food.getSpecialOfTheDay() == "Binary Burger");
        food.update(TechSignal("full_capacity", "All chairs occupied"));
        food.update(TechSignal("network_failure", "Card system offline"));
        food.update(TechSignal("emergency_pause", "Safety drill"));
        food.update(TechSignal("resume", "Safety drill complete"));
        std::cout << food.getStatus();
    }

    void testAIZone()
    {
        heading("5. AIZone composite (Delegation Container)");

        AIZone zone(nullptr);
        AIDemoBooth *ai = new AIDemoBooth(&zone);
        RoboticsBooth *robotics = new RoboticsBooth(&zone);

        zone.add(ai);
        zone.add(robotics);
        assert(zone.hasChildren());

        int cap = zone.getCapacity(); // Combined capacity of leaf booths

        // Admission fails when closed
        assert(zone.enterVisitor(10) == 0);

        zone.open();

        // Oversubscribed entry: returns exactly what children can take
        int admitted = zone.enterVisitor(cap + 10);
        assert(admitted == cap);
        assert(zone.getCurrentVisitors() == cap);

        // Oversubscribed removal: returns exactly what is currently inside
        int removed = zone.leaveVisitor(cap + 10);
        assert(removed == cap);
        assert(zone.getCurrentVisitors() == 0);

        // Clean up dynamic leaf pointers attached to the composite
        delete ai;
        delete robotics;
    }

    void testRegistryFactoryAndRemoval()
    {
        heading("6. ExpoRegistry factory and removal");

        ExpoRegistry registry;
        EventComponent *hall = registry.createComponent(
            ExpoRegistry::ComponentType::EXHIBITION_HALL, nullptr);
        EventComponent *stage = registry.createComponent(
            ExpoRegistry::ComponentType::MAIN_STAGE, hall);
        EventComponent *keynote = registry.createComponent(
            ExpoRegistry::ComponentType::KEYNOTE_AREA, stage);
        EventComponent *demo = registry.createComponent(
            ExpoRegistry::ComponentType::DEMO_AREA, stage);

        assert(hall != nullptr && stage != nullptr && keynote != nullptr && demo != nullptr);

        // Find using internal class default names or lookup keys
        assert(registry.findComponent("does_not_exist") == nullptr);

        std::string stageName = stage->getName();
        std::string keynoteName = keynote->getName();
        std::string demoName = demo->getName();
        std::string hallName = hall->getName();

        assert(!registry.removeComponent("does_not_exist"));
        assert(!registry.removeComponent(stageName)); // Node with active children cannot be removed
        assert(registry.removeComponent(demoName));
        assert(registry.removeComponent(keynoteName));
        assert(registry.removeComponent(stageName));
        assert(registry.removeComponent(hallName));
    }

    void testEventScenario()
    {
        heading("7. EventFlow static demonstration");

        ExpoRegistry registry;
        MapBuilder builder;
        builder.build(registry);

        // Flexible lookup: search for main hall/stage components dynamically
        EventComponent *hall = registry.findComponent("Main_Exhibition_Hall");
        if (!hall)
            hall = registry.findComponent("Exhibition_Hall");

        EventComponent *stage = registry.findComponent("Main_Stage");
        if (!stage)
            stage = registry.findComponent("MainStage");

        EventComponent *keynote = registry.findComponent("Keynote_Area");
        if (!keynote)
            keynote = registry.findComponent("KeyNoteArea");

        EventComponent *demo = registry.findComponent("Demo_Area");
        if (!demo)
            demo = registry.findComponent("DemoArea");

        assert(hall != nullptr);

        if (stage && keynote && demo)
        {
            MainStage *mainStage = dynamic_cast<MainStage *>(stage);
            KeyNoteArea *keynoteArea = dynamic_cast<KeyNoteArea *>(keynote);
            DemoArea *demoArea = dynamic_cast<DemoArea *>(demo);

            if (mainStage)
            {
                mainStage->advanceStaff();
                std::cout << mainStage->getStatus();
            }
            if (keynoteArea)
            {
                keynoteArea->advancePresenter();
                keynoteArea->pausePresenterTimer();
                keynoteArea->resumePresenterTimer();
                std::cout << keynoteArea->getStatus();
            }
            if (demoArea)
            {
                demoArea->setHandsOnAllowed(true);
                demoArea->advanceDemo();
                demoArea->pauseDemoTimer();
                demoArea->resumeDemoTimer();
                std::cout << demoArea->getStatus();
            }
        }

        registry.printMap();
        hall->open();

        assert(hall->getCapacity() > 0);
        registry.printCapacity("missing_component");

        assert(!registry.transmitSignal("missing_component", TechSignal("open")));
        registry.printStatusReport();
        hall->close();
    }

    void testTechnician()
    {
        heading("8. Technician value object");

        Technician technician("Ace Lovelove", "012 345 6789");
        assert(static_cast<std::string>(technician) == "Ace Lovelove (012 345 6789)");
    }

}

int main()
{
    std::cout << "EventFlow static test harness\n";
    testTechSignals();
    testObserver();
    testTimer();
    testStandaloneLeaves();
    testAIZone();
    testRegistryFactoryAndRemoval();
    testEventScenario();
    testTechnician();

    std::cout << "\nAll static tests completed successfully.\n";
    return 0;
}