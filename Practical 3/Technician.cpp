#include "Technician.h"


Technician::Technician(std::string name, std::string contactInfo) : name(name), contactInfo(contactInfo) {}

std::string Technician::getName() const {
    return name;
}

std::string Technician::getContactInfo() const {
    return contactInfo;
}

Technician::operator std::string() const {
    return name + " (" + contactInfo + ")";
}