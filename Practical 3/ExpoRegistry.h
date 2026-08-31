#ifndef EXPOREGISTRY_H
#define EXPOREGISTRY_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "EventComponent.h"
#include "TechSignal.h"

/**
 * @class ExpoRegistry
 * @brief Central facade, factory, and lookup registry for managing the entire expo hierarchy.
 * 
 * Encapsulates component creation, map generation, tree printing, component lookup via std::unordered_map, 
 * relocation wrapper methods, visitor management, and signal transmission initiation.
 */
class ExpoRegistry {
public:
    ExpoRegistry() = default;
    ~ExpoRegistry() = default;

    // Prevent copying to maintain valid unique component references
    ExpoRegistry(const ExpoRegistry&) = delete;
    ExpoRegistry& operator=(const ExpoRegistry&) = delete;

    // Supported component type identifiers for factory creation
    enum class ComponentType {
        EXHIBITION_HALL,
        MAIN_STAGE,
        KEYNOTE_AREA,
        DEMO_AREA
    };

    /**
     * @brief Factory method to create, register, and manage a new event component.
     * @param type The ComponentType enum indicating which subclass to instantiate.
     * @param name Name of the component.
     * @param parentName Optional name of the parent component to attach to (default: empty).
     * @return EventComponent* Pointer to the created component, or nullptr on failure.
     */
    EventComponent* createComponent(ComponentType type, const std::string& parentName = "");

    /**
     * @brief Unregisters and destroys a component from the registry by name.
     * @param name Name of the component to remove.
     * @return true if removed, false if not found.
     */
    bool removeComponent(const std::string& name);

    /**
     * @brief Finds a component in the lookup table by name.
     * @param name Name of the component.
     * @return EventComponent* Pointer to the component, or nullptr if not found.
     */
    EventComponent* findComponent(const std::string& name) const;

    /**
     * @brief Relocates a component to a new parent composite using operator>>.
     * @param childName Name of the component to move.
     * @param newParentName Name of the target destination parent composite.
     * @return true if successfully relocated, false otherwise.
     */
    bool moveComponent(const std::string& childName, const std::string& newParentName);

    /**
     * @brief Transmits a technical signal to a target composite node or root.
     * @param targetName Name of the broadcaster component to initiate signal transmission.
     * @param signal TechSignal instance to transmit.
     * @return true if signal was successfully dispatched, false otherwise.
     */
    bool transmitSignal(const std::string& targetName, const TechSignal& signal);

    /**
     * @brief Displays visitor capacity and current count for a specified component.
     * @param componentName Name of the component.
     */
    void printCapacity(const std::string& componentName) const;

    /**
     * @brief Admits visitors into a specific component.
     * @param componentName Name of target component.
     * @param count Number of visitors entering.
     * @return Number of visitors actually admitted.
     */
    int enterVisitors(const std::string& componentName, int count);

    /**
     * @brief Removes visitors from a specific component.
     * @param componentName Name of target component.
     * @param count Number of visitors leaving.
     * @return Number of visitors actually removed.
     */
    int leaveVisitors(const std::string& componentName, int count);

    /**
     * @brief Prints a textual representation/map of the hierarchy rooted at a given component.
     * @param rootName Name of the root component to print from (default: empty for all root nodes).
     */
    void printMap(const std::string& rootName = "") const;

    /**
     * @brief Prints the operational status report of all registered components.
     */
    void printStatusReport() const;

private:
    std::unordered_map<std::string, std::unique_ptr<EventComponent>> registryMap; /**< Ownership storage */
    std::unordered_map<std::string, EventComponent*> lookupTable;                 /**< Lookup map */

    void printTreeRecursive(const EventComponent* component, int depth) const;
};

#endif /* EXPOREGISTRY_H */