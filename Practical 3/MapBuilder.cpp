#include "MapBuilder.h"
#include "ExpoRegistry.h"
#include "EventComponent.h"

void MapBuilder::build(ExpoRegistry& registry) {
    // 1. Top-level Root Composite
    EventComponent* exhibitionHall = registry.createComponent(
        ExpoRegistry::ComponentType::EXHIBITION_HALL, nullptr
    );

    // 2. Sub-Composites under Exhibition Hall
    EventComponent* mainStage = registry.createComponent(
        ExpoRegistry::ComponentType::MAIN_STAGE, exhibitionHall
    );

    EventComponent* aiZone = registry.createComponent(
        ExpoRegistry::ComponentType::AI_ZONE, exhibitionHall
    );

    // 3. Leaf Node directly under Exhibition Hall
    registry.createComponent(
        ExpoRegistry::ComponentType::BYTE_SIZED_BITES, exhibitionHall
    );

    // 4. Leaf Nodes under Main Stage
    registry.createComponent(
        ExpoRegistry::ComponentType::KEYNOTE_AREA, mainStage
    );

    registry.createComponent(
        ExpoRegistry::ComponentType::DEMO_AREA, mainStage
    );

    // 5. Leaf Nodes under AI Zone
    registry.createComponent(
        ExpoRegistry::ComponentType::AI_DEMO_BOOTH, aiZone
    );

    registry.createComponent(
        ExpoRegistry::ComponentType::ROBOTICS_BOOTH, aiZone
    );
}