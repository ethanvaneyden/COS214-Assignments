#include "RestApiFactory.h"
#include "RestApiConnector.h"

Connector *RestApiFactory::createConnector()
{
    return new RestApiConnector();
}