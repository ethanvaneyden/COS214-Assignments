#include "TechSignal.h"
#include <unordered_map>
using namespace std;

TechSignal::TechSignal(const string &type, const string &priority,
                       const string &message) {
  this->type = parseType(type);
  this->priority = parsePriority(priority);
  this->message = message;
}

TechSignal::TechSignal(const string &type, const string &message) {
  this->type = parseType(type);
  this->priority = inferPriority(this->type);
  this->message = message;
}

TechSignal::TechSignal(TechSignal::Type type, TechSignal::Priority priority,
                       const string &message) {
  this->type = type;
  this->priority = priority;
  this->message = message;
}

TechSignal::TechSignal(TechSignal::Type type, const string &message) {
  this->type = type;
  this->priority = inferPriority(type);
  this->message = message;
}

TechSignal::Type TechSignal::parseType(const std::string &typeStr) const {
  const unordered_map<string, TechSignal::Type> types = {
      {"open", TechSignal::Type::OPEN},
      {"close", TechSignal::Type::CLOSE},
      {"resume", TechSignal::Type::RESUME},
      {"full_capacity", TechSignal::Type::FULL_CAPACITY},
      {"change_schedule", TechSignal::Type::SCHEDULE_CHANGE},
      {"power_failure", TechSignal::Type::POWER_FAILURE},
      {"emergency_pause", TechSignal::Type::EMERGENCY_PAUSE},
      {"network_failure", TechSignal::Type::NETWORK_FAILURE}};

  auto it = types.find(typeStr);
  if (it != types.end()) {
    return it->second;
  }

  return TechSignal::Type::UNKNOWN;
}

TechSignal::Priority
TechSignal::parsePriority(const std::string &priorityString) const {
  const unordered_map<string, TechSignal::Priority> priorities = {
      {"low", TechSignal::Priority::LOW},
      {"medium", TechSignal::Priority::MEDIUM},
      {"high", TechSignal::Priority::HIGH},
      {"critical", TechSignal::Priority::CRITICAL}};

  auto it = priorities.find(priorityString);
  if (it != priorities.end()) {
    return it->second;
  }

  return TechSignal::Priority::UNKNOWN;
}

TechSignal::Priority TechSignal::inferPriority(TechSignal::Type type) {
  switch (type) {
  case Type::OPEN:
  case Type::CLOSE:
  case Type::RESUME:
    return Priority::LOW;

  case Type::FULL_CAPACITY:
  case Type::SCHEDULE_CHANGE:
    return Priority::MEDIUM;

  case Type::POWER_FAILURE:
  case Type::NETWORK_FAILURE:
    return Priority::HIGH;

  case Type::EMERGENCY_PAUSE:
    return Priority::CRITICAL;

  default:
    return Priority::UNKNOWN;
  }
}

TechSignal::Type TechSignal::getType() const { return type; }

TechSignal::Priority TechSignal::getPriority() const { return priority; }

string TechSignal::getMessage() const { return message; }
