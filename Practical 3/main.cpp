#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
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
        RecordingSubscriber() : notifications(0), lastType(TechSignal::Type::UNKNOWN) {}

        void update(const TechSignal& signal) override {
            ++notifications;
            lastType = signal.getType();
        }

        int notifications;
        TechSignal::Type lastType;
    };

    void heading(const char* text) {
        std::cout << "\n====================================================\n"
                  << text << "\n"
                  << "====================================================\n";
    }

    void testTechSignals() {
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

    void testObserver() {
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

    void testTimer() {
        heading("3. BackgroundTimer states");

        std::atomic<int> ticks(0);
        BackgroundTimer timer;
        timer.start(std::chrono::milliseconds(10), [&ticks]() { ++ticks; });
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

    void testStandaloneLeaves() {
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

    void testAIZone() {
        heading("5. AIZone composite (Delegation)");

        AIZone zone(nullptr);
        AIDemoBooth* ai = new AIDemoBooth(&zone);
        RoboticsBooth* robotics = new RoboticsBooth(&zone);

        zone.add(nullptr);
        zone.add(ai);
        zone.add(ai); // Duplicate check
        zone.add(robotics);
        assert(zone.hasChildren());

        int cap = zone.getCapacity();
        assert(cap > 0);

        zone.open();
        ai->open();
        robotics->open();

        // Delegation test: fill composite via delegation
        int admitted = zone.enterVisitor(cap + 10);
        assert(admitted == cap);
        assert(zone.getCurrentVisitors() == cap);

        int removed = zone.leaveVisitor(cap + 10);
        assert(removed == cap);
        assert(zone.getCurrentVisitors() == 0);

        zone.update(TechSignal("network_failure", "Wireless maintenance"));
        zone.update(TechSignal("emergency_pause", "Safety drill"));
        zone.update(TechSignal("resume", "Safety drill complete"));
        std::cout << zone.getStatus();

        zone.remove(ai);
        zone.remove(ai);
        assert(ai->getParent() == nullptr);

        delete ai;
        delete robotics;
    }

    void testRegistryFactoryAndRemoval() {
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

        // Retrieve actual keys dynamically using getName()
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

    void testEventScenario() {
        heading("7. EventFlow static demonstration");

        ExpoRegistry registry;
        MapBuilder builder;
        builder.build(registry);

        // Dynamic lookups via getName() to support varying internal default strings
        EventComponent* hall = nullptr;
        EventComponent* stage = nullptr;
        EventComponent* keynote = nullptr;
        EventComponent* demo = nullptr;

        const char* hallKeys[] = {"Main_Exhibition_Hall", "Exhibition_Hall", "ExhibitionHall"};
        const char* stageKeys[] = {"Main_Stage", "MainStage"};
        const char* keynoteKeys[] = {"Keynote_Area", "KeyNoteArea"};
        const char* demoKeys[] = {"Demo_Area", "DemoArea"};

        for (const char* key : hallKeys) { if ((hall = registry.findComponent(key))) break; }
        for (const char* key : stageKeys) { if ((stage = registry.findComponent(key))) break; }
        for (const char* key : keynoteKeys) { if ((keynote = registry.findComponent(key))) break; }
        for (const char* key : demoKeys) { if ((demo = registry.findComponent(key))) break; }

        assert(hall != nullptr);

        if (stage && keynote && demo) {
            MainStage* mainStage = dynamic_cast<MainStage*>(stage);
            KeyNoteArea* keynoteArea = dynamic_cast<KeyNoteArea*>(keynote);
            DemoArea* demoArea = dynamic_cast<DemoArea*>(demo);

            assert(stage->getParent() == hall);
            assert(keynote->getParent() == stage);
            assert(demo->getParent() == stage);

            if (mainStage) {
                if (!mainStage->getStaff().empty()) mainStage->advanceStaff();
                std::cout << mainStage->getStatus();
            }
            if (keynoteArea) {
                if (!keynoteArea->getPresenter().empty()) keynoteArea->advancePresenter();
                keynoteArea->pausePresenterTimer();
                keynoteArea->resumePresenterTimer();
                std::cout << keynoteArea->getStatus();
            }
            if (demoArea) {
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

    void testTechnician() {
        heading("8. Technician value object");

        Technician technician("Ace Lovelove", "012 345 6789");
        assert(static_cast<std::string>(technician) == "Ace Lovelove (012 345 6789)");
    }

}

int main() {
    std::cout << "EventFlow static test harness\n";
    testTechSignals();
    testObserver();
    testTimer();
    testStandaloneLeaves();
    testAIZone();
    testRegistryFactoryAndRemoval();
    testEventScenario();
    testTechnician();
    
    // Uncomment runGame() to launch CLI mode
    // runGame();
    
    std::cout << "\nAll static tests completed successfully.\n";
    return 0;
}

void printHelp() {
    std::cout
        << "\n================ EXPO COMMAND MENU ================\n"
        << "  map                              : Print the EXPO map\n"
        << "  status                           : Print operational status report\n"
        << "  capacity <name>                  : Show capacity info for a component\n"
        << "  enter <name> <count>             : Admit visitors into a component\n"
        << "  leave <name> <count>             : Remove visitors from a component\n"
        << "  signal <target> <type>           : Send a TechSignal\n"
        << "  move <child> <new_parent>        : Relocate a component using operator>>\n"
        << "  help                             : Show this menu\n"
        << "  exit                             : Quit application\n"
        << "===================================================\n\n";
}

void runGame() {
    ExpoRegistry registry;
    MapBuilder mapBuilder;
    mapBuilder.build(registry);

    EventComponent* hall = registry.findComponent("Main_Exhibition_Hall");
    if (!hall) hall = registry.findComponent("ExhibitionHall");
    if (!hall) hall = registry.findComponent("Exhibition_Hall");

    if (hall) {
        hall->open();
    } else {
        std::cerr << "[Main Error] Exhibition Hall could not be found in the registry.\n";
    }

    std::cout
        << "====================================================\n"
        << "      WELCOME TO THE EXPO MANAGEMENT SYSTEM         \n"
        << "====================================================\n";

    printHelp();

    std::string line;

    while (true) {
        std::cout << "EventFlow> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit" || command == "quit") {
            std::cout << "Exiting Expo System. Goodbye!\n";
            break;
        }
        else if (command == "map") {
            registry.printMap();
        }
        else if (command == "status") {
            registry.printStatusReport();
        }
        else if (command == "help") {
            printHelp();
        }
        else if (command == "capacity") {
            std::string name;
            if (ss >> name) {
                registry.printCapacity(name);
            } else {
                std::cout << "Usage: capacity <component_name>\n";
            }
        }
        else if (command == "enter") {
            std::string name;
            int count = 0;
            if (ss >> name >> count) {
                int admitted = registry.enterVisitors(name, count);
                std::cout << "[Registry] Admitted " << admitted << " visitors to '" << name << "'.\n";
            } else {
                std::cout << "Usage: enter <component_name> <count>\n";
            }
        }
        else if (command == "leave") {
            std::string name;
            int count = 0;
            if (ss >> name >> count) {
                int removed = registry.leaveVisitors(name, count);
                std::cout << "[Registry] Removed " << removed << " visitors from '" << name << "'.\n";
            } else {
                std::cout << "Usage: leave <component_name> <count>\n";
            }
        }
        else if (command == "move") {
            std::string childName;
            std::string parentName;
            if (ss >> childName >> parentName) {
                if (registry.moveComponent(childName, parentName)) {
                    std::cout << "[Registry] Moved '" << childName << "' to '" << parentName << "' via operator>>.\n";
                }
            } else {
                std::cout << "Usage: move <child_name> <new_parent_name>\n";
            }
        }
        else if (command == "signal") {
            std::string targetName;
            std::string signalTypeStr;
            if (ss >> targetName >> signalTypeStr) {
                TechSignal signal(signalTypeStr, "Broadcasting user-issued CLI signal.");
                if (registry.transmitSignal(targetName, signal)) {
                    std::cout << "[Registry] TechSignal dispatched to '" << targetName << "'.\n";
                }
            } else {
                std::cout << "Usage: signal <target_name> <signal_type>\n";
            }
        }
        else {
            std::cout << "Unknown command. Type 'help' for available options.\n";
        }
    }
}