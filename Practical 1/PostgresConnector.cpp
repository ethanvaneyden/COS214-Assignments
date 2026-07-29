#include "PostgresConnector.h"

PostgresConnector::PostgresConnector() : Connector("postgres") {}

vector<string> PostgresConnector::extract() {
    return {"PG:001", "PG:002", "PG:002", "PG:003"};
}