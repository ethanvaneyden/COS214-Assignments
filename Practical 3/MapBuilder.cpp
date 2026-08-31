#include "MapBuilder.h"
#include "ExpoRegistry.h"

void MapBuilder::build(ExpoRegistry& registry) {
    EventComponent* mainHall =
    registry.createComponent(
        ExpoRegistry::ComponentType::EXHIBITION_HALL, nullptr
    );

EventComponent* mainStage =
    registry.createComponent(
        ExpoRegistry::ComponentType::MAIN_STAGE,
        mainHall
    );

registry.createComponent(
    ExpoRegistry::ComponentType::KEYNOTE_AREA,
    mainStage
);

registry.createComponent(
    ExpoRegistry::ComponentType::DEMO_AREA,
    mainStage
);

}