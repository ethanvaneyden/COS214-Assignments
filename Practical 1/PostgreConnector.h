#ifndef POSTGRECON_H
#define POSTGRECON_H

#include "Connector.h"

class PostgreConnector : public Connector {
    public:
    vector<string> extract();
};

#endif