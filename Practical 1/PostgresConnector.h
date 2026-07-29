#ifndef POSTGRESCON_H
#define POSTGRESCON_H

#include "Connector.h"

class PostgresConnector : public Connector {
    public:
    PostgresConnector();
    vector<string> extract();
};

#endif