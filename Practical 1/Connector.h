#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <vector>
#include <string>

class Connector
{
public:
    Connector(const std::string &);
    virtual std::vector<std::string> extract() = 0;
    std::string getSource();
    virtual ~Connector();

protected:
    std::string source;
};

#endif