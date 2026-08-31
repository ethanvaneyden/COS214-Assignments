#ifndef MAINSTAGE_H
#define MAINSTAGE_H

#include "EventComposite.h"
#include <atomic>
#include <chrono>
#include <string>
#include <vector>

// Forward declarations
class TechSignal;
class BackgroundTimer;
class Technician;

/**
 * @class MainStage
 * @brief Composite node in the hierarchy that holds child components
 *        and manages active technician rotations.
 */
class MainStage : public EventComposite {
public:
  /**
   * @brief Construct a new MainStage composite object.
   * @param parent Pointer to the parent component in the hierarchy (default:
   * nullptr).
   */
  explicit MainStage(EventComponent *parent = nullptr);

  /**
   * @brief Destructor that cleans up dynamic timer allocations.
   */
  ~MainStage() override;

  /**
   * @brief Receives a signal and broadcasts it to all child subscribers.
   * @param signal The TechSignal to propagate down the tree.
   */
  void update(const TechSignal &signal) override;

  /**
   * @brief Starts the background rotation timer for technical staff.
   */
  void startStaffTimer();

  /**
   * @brief Stops the background rotation timer for technical staff.
   */
  void stopStaffTimer();

  /**
   * @brief Advances the technician index to the next staff member in rotation.
   */
  void advanceStaff();

  /**
   * @brief Overrides Component method to provide the current technician on
   * duty.
   * @return std::string Information of current technician, or delegates to
   * parent.
   */
  std::string getStaff() const override;

  void open() override;
  void close() override;

  int getCapacity() const override;
  int enterVisitor(int visitors) override;
  int leaveVisitor(int visitors) override;
  int getCurrentVisitors() const override;

  /**
   * @brief Recursively collects and formats the status of all child components.
   * @return std::string Summary status string for the stage and its
   * sub-components.
   */
  std::string getStatus() const override;

private:
  std::vector<Technician> staff; /**< Roster of technicians assigned to stage */
  std::atomic<size_t> staffIndex{
      0}; /**< Thread-safe index for current staff member */

  std::chrono::minutes staffInterval; /**< Time interval between staff rotations */
  BackgroundTimer* staffTimer; /**< Background timer thread for staff rotation */
};

#endif /* MAINSTAGE_H */