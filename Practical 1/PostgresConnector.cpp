#include "PostgresConnector.h"

PostgresConnector::PostgresConnector() : Connector("postgres") {}

std::vector<std::string> PostgresConnector::extract()
{
    return {"PG:001", "PG:002", "PG:002", "PG:003"};
}