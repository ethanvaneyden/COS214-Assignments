#ifndef RESTCON_H
#define RESTCON_H

#include "Connector.h"

class RestApiConnector : public Connector
{
public:
    RestApiConnector();
    std::vector<std::string> extract();
};

#endif