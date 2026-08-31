#include "ExpoRegistry.h"
#include "DemoArea.h"
#include "ExhibitionHall.h"
#include "KeyNoteArea.h"
#include "MainStage.h"
#include <iostream>

EventComponent *ExpoRegistry::createComponent(ComponentType type,
                                              const std::string &parentName) {
  EventComponent *parent =
      !parentName.empty() ? findComponent(parentName) : nullptr;
  std::unique_ptr<EventComponent> newComponent;

  switch (type) {
  case ComponentType::EXHIBITION_HALL:
    newComponent.reset(new ExhibitionHall());
    break;
  case ComponentType::MAIN_STAGE:
    newComponent.reset(new MainStage(parent));
    break;
  case ComponentType::KEYNOTE_AREA:
    newComponent.reset(new KeyNoteArea(parent));
    break;
  case ComponentType::DEMO_AREA:
    newComponent.reset(new DemoArea(parent));
    break;
  }

  if (!newComponent)
    return nullptr;

  std::string name = newComponent->getName();
  EventComponent *rawPtr = newComponent.get();

  // Attach to parent composite if specified
  if (parent) {
    parent->add(rawPtr);
  }

  lookupTable[name] = rawPtr;
  registryMap[name] = std::move(newComponent);

  return rawPtr;
}

bool ExpoRegistry::removeComponent(const std::string &name) {
  auto it = lookupTable.find(name);
  if (it == lookupTable.end())
    return false;

  EventComponent *comp = it->second;

  // Don't remove a composite that still contains children.
  if (comp && comp->hasChildren()) {
    return false;
  }

  if (comp && comp->getParent()) {
    comp->getParent()->remove(comp);
  }

  lookupTable.erase(name);
  registryMap.erase(name);

  return true;
}

EventComponent *ExpoRegistry::findComponent(const std::string &name) const {
  auto it = lookupTable.find(name);
  if (it != lookupTable.end()) {
    return it->second;
  }
  return nullptr;
}

bool ExpoRegistry::moveComponent(const std::string &childName,
                                 const std::string &newParentName) {
  EventComponent *child = findComponent(childName);
  EventComponent *newParent = findComponent(newParentName);

  if (!child || !newParent) {
    std::cerr << "[ExpoRegistry Error] Failed to move: component(s) not found "
                 "in registry.\n";
    return false;
  }

  (*child) >> (*newParent);
  return true;
}

bool ExpoRegistry::transmitSignal(const std::string &targetName,
                                  const TechSignal &signal) {
  EventComponent *target = findComponent(targetName);
  if (!target) {
    std::cerr << "[ExpoRegistry Error] Target '" << targetName
              << "' not found for signal transmission.\n";
    return false;
  }

  target->update(signal);
  return true;
}

void ExpoRegistry::printCapacity(const std::string &componentName) const {
  EventComponent *comp = findComponent(componentName);
  if (!comp) {
    std::cout << "[ExpoRegistry] Component '" << componentName
              << "' not found.\n";
    return;
  }

  std::cout << "[Capacity Info] " << comp->getName() << ": "
            << comp->getCurrentVisitors() << " / " << comp->getCapacity()
            << " visitors.\n";
}

int ExpoRegistry::enterVisitors(const std::string &componentName, int count) {
  EventComponent *comp = findComponent(componentName);
  if (!comp)
    return 0;
  return comp->enterVisitor(count);
}

int ExpoRegistry::leaveVisitors(const std::string &componentName, int count) {
  EventComponent *comp = findComponent(componentName);
  if (!comp)
    return 0;
  return comp->leaveVisitor(count);
}

void ExpoRegistry::printMap(const std::string &rootName) const {
  std::cout << "\n================ EXPO MAP ================\n";
  if (!rootName.empty()) {
    EventComponent *root = findComponent(rootName);
    if (root) {
      printTreeRecursive(root, 0);
    } else {
      std::cout << "Root component '" << rootName << "' not found.\n";
    }
  } else {
    for (const auto &pair : lookupTable) {
      if (pair.second && pair.second->getParent() == nullptr) {
        printTreeRecursive(pair.second, 0);
      }
    }
  }
  std::cout << "==========================================\n\n";
}

void ExpoRegistry::printTreeRecursive(const EventComponent *component,
                                      int depth) const {
  if (!component)
    return;

  std::string indent(depth * 4, ' ');
  std::cout << indent << "|-- " << component->getName() << " ("
            << component->getStaff() << ")" << "\n";
}

void ExpoRegistry::printStatusReport() const {
  std::cout << "\n============= STATUS REPORT =============\n";
  for (const auto &pair : lookupTable) {
    if (pair.second) {
      pair.second->reportStatus();
    }
  }
  std::cout << "==========================================\n\n";
}