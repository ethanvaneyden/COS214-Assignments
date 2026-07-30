#ifndef POSTGRESCON_H
#define POSTGRESCON_H

#include "Connector.h"

class PostgresConnector : public Connector
{
public:
    PostgresConnector();
    std::vector<std::string> extract();
};

#endif