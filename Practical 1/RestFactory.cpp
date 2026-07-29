#include "RestApiFactory.h"
#include "RestApiConnector.h"

Connector* createConnector() {
    return new RestApiConnector();
}