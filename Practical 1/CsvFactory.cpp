#include "CsvFactory.h"
#include "CsvConnector.h"

Connector* CsvFactory::createConnector() {
    return new CsvConnector();
}