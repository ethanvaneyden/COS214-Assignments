#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include <string>

class Technician {
public:
    Technician(std::string name, std::string contactInfo);
    ~Technician() = default;
    operator std::string() const;
private:
    std::string name;
    std::string contactInfo;
};
#endif /* TECHNICIAN_H */