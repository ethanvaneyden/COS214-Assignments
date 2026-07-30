#ifndef CSVCON_H
#define CSVCON_H

#include "Connector.h"

class CsvConnector : public Connector
{

public:
    CsvConnector();
    std::vector<std::string> extract();
};

#endif