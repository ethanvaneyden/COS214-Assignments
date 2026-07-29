#include "RestApiConnector.h"

RestApiConnector::RestApiConnector() : Connector("restapi") {}

std::vector<std::string> RestApiConnector::extract()
{
    return {"API:44", "API:45", "API:45"};
}