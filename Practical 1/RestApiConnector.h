#ifndef RESTCON_H
#define RESTCON_H

#include "Connector.h"

class RestApiConnector : public Connector {
    public:
    RestApiConnector();
    vector<string> extract();

};

#endif