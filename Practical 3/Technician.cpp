#include "Technician.h"


Technician::Technician(std::string name, std::string contactInfo) : name(name), contactInfo(contactInfo) {}

Technician::operator std::string() const {
    return name + " (" + contactInfo + ")";
}