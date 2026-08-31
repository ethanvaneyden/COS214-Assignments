#include "MapBuilder.h"
#include "ExpoRegistry.h"

void MapBuilder::build(ExpoRegistry& registry) {
    registry.createComponent(ExpoRegistry::ComponentType::EXHIBITION_HALL);
    registry.createComponent(ExpoRegistry::ComponentType::MAIN_STAGE, "Main Exhibition Hall");
    registry.createComponent(ExpoRegistry::ComponentType::KEYNOTE_AREA, "Main Stage");
    registry.createComponent(ExpoRegistry::ComponentType::DEMO_AREA, "Main Stage");

}