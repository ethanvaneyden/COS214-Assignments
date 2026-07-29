#include "RestApiConnector.h"

RestApiConnector::RestApiConnector() : Connector("restapi") {}

vector<string> RestApiConnector::extract() {
    return {"API:44","API:45","API:45"};
}