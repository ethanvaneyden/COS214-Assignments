#include "MapBuilder.h"
#include "ExpoRegistry.h"
#include "EventComponent.h"

void MapBuilder::build(ExpoRegistry& registry) {
    // 1. Create top-level Root Composite
    EventComponent* exhibitionHall = registry.createComponent(
        ExpoRegistry::ComponentType::EXHIBITION_HALL, nullptr
    );

    // 2. Create Composites under Exhibition Hall
    EventComponent* mainStage = registry.createComponent(
        ExpoRegistry::ComponentType::MAIN_STAGE, exhibitionHall
    );

    EventComponent* aiZone = registry.createComponent(
        ExpoRegistry::ComponentType::AI_ZONE, exhibitionHall
    );

    // 3. Create Leaf Nodes directly under Exhibition Hall
    EventComponent* byteSizedBites = registry.createComponent(
        ExpoRegistry::ComponentType::BYTE_SIZED_BITES, exhibitionHall
    );

    // 4. Create Leaf Nodes under Main Stage
    EventComponent* keynoteArea = registry.createComponent(
        ExpoRegistry::ComponentType::KEYNOTE_AREA, mainStage
    );

    // 5. Create Leaf Nodes under AI Zone
    EventComponent* aiDemoBooth = registry.createComponent(
        ExpoRegistry::ComponentType::AI_DEMO_BOOTH, aiZone
    );

    EventComponent* roboticsBooth = registry.createComponent(
        ExpoRegistry::ComponentType::ROBOTICS_BOOTH, aiZone
    );

    // 6. Build Composite Tree hierarchy directly
    exhibitionHall->add(mainStage);
    exhibitionHall->add(aiZone);
    exhibitionHall->add(byteSizedBites);

    mainStage->add(keynoteArea);

    aiZone->add(aiDemoBooth);
    aiZone->add(roboticsBooth);
}