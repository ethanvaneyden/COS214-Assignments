#include "CsvConnector.h"

CsvConnector::CsvConnector() : Connector("csv") {}

std::vector<std::string> CsvConnector::extract()
{
    return {"CSV:x1", "CSV:x2", "CSV:x3", "CSV:x3"};
}