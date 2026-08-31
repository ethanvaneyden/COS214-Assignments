#ifndef MAPBUILDER_H
#define MAPBUILDER_H

class ExpoRegistry;
/**
 * @brief This class is responsible for constructing the map
 *
 */
class MapBuilder {
public:
  /**
   * @brief Populates the registry in the paramater
   *
   * @param registry
   */
  void build(ExpoRegistry &registry);
  /**
   * @brief Construct a new Map Builder object
   *
   */
  MapBuilder() = default;
  /**
   * @brief Destroy the Map Builder object
   *
   */
  ~MapBuilder() = default;
};

#endif