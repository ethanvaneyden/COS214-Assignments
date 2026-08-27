#ifndef TECHSIGNAL_H
#define TECHSIGNAL_H

#include <string>

class TechSignal {
public:
  enum class Type {
    UNKNOWN,
    OPEN,
    CLOSED,
    FULL_CAPACITY,
    SCHEDULE_CHANGE,
    POWER_FAILURE,
    EMERGENCY_PAUSE,
    NETWORK_FAILURE
  };
  enum class Priority { UNKNOWN, LOW, MEDIUM, HIGH, CRITICAL };

private:
  Type type;
  Priority priority;
  std::string message;
  Type parseType(const std::string &typeStr) const;
  Priority parsePriority(const std::string &priorityStr) const;

public:
  /**
   * @brief Construct a new Tech Signal object
   *
   * @param type
   * @param priority
   * @param message
   */
  TechSignal(const std::string &type, const std::string &priority,
             const std::string &message);
  /**
   * @brief Construct a new Tech Signal object
   *
   * @param type
   * @param message
   */
  TechSignal(const std::string &type, const std::string &message = "");
  /**
   * @brief Destroy the Tech Signal object
   *
   */
  ~TechSignal() = default;
  /**
   * @brief Get the type
   *
   * @return Type
   */
  Type getType() const;
  /**
   * @brief Get the priority
   *
   * @return Priority
   */
  Priority getPriority() const;
  /**
   * @brief Get the message
   *
   * @return std::string
   */
  std::string getMessage() const;
};

#endif