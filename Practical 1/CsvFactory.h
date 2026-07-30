#ifndef CSVFACTORY_H
#define CSVFACTORY_H

#include "ConnectorFactory.h"

class CsvFactory : public ConnectorFactory
{
public:
    Connector *createConnector();
};

#endif