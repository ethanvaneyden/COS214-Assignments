#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include <string>

class Technician {
public:
    Technician(std::string name, std::string contactInfo);
    ~Technician() = default;

    std::string getName() const;
    std::string getContactInfo() const;
    operator std::string() const;
private:
    std::string name;
    std::string contactInfo;
};
#endif /* TECHNICIAN_H */