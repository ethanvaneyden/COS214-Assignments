#ifndef RESTFACTORY_H
#define RESTFACTORY_H

#include "ConnectorFactory.h"

class RestApiFactory : public ConnectorFactory {
    public:
    Connector* createConnector();
};

#endif