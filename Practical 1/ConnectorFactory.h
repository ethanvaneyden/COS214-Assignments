#ifndef CONFACTORY_H
#define CONFACTORY_H

#include "Connector.h"

class ConnectorFactory {

    public:
    virtual Connector* createConnector() = 0;
    virtual ~ConnectorFactory();
    
};

#endif