#ifndef TECHSIGNAL_H
#define TECHSIGNAL_H

#include <string>

class TechSignal
{
public:
    enum class Type
    {
        UNKNOWN,
        OPEN,
        CLOSED,
        FULL_CAPACITY,
        SCHEDULE_CHANGE,
        POWER_FAILURE,
        EMERGENCY_PAUSE
    };
    enum class Priority
    {
        UNKNOWN,
        LOW,
        MEDIUM,
        HIGH,
        CRITICAL
    };

private:
    Type type;
    Priority priority;
    std::string message;
    Type parseType(const std::string &typeStr) const;
    Priority parsePriority(const std::string &priorityStr) const;

public:
    TechSignal(const std::string &type, const std::string &priority, const std::string &message);
    TechSignal(const std::string &type, const std::string &message = "");
    ~TechSignal() = default;
    Type getType() const;
    Priority getPriority() const;
    std::string getMessage() const;
};

#endif