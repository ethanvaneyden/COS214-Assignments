#include <iostream>
#include <vector>
#include <string>

#include "PostgresConnector.h"
#include "RestApiConnector.h"
#include "CsvConnector.h"
#include "PostgresFactory.h"
#include "RestApiFactory.h"
#include "CsvFactory.h"

void printRecords(const std::string &label, const std::vector<std::string> &records)
{
    std::cout << label << ": ";
    std::size_t counter = 0;
    for (const auto &record : records)
    {
        if (counter == records.size() - 1)
        {
            std::cout << record;
        }
        else
        {
            std::cout << record << ", ";
        }
        counter++;
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "TEST 1: Testing Concrete Connectors (Directly)" << std::endl;
    std::cout << "========================================" << std::endl;

    // Test PostgresConnector
    PostgresConnector pgConn;
    std::cout << "Postgres source: " << pgConn.getSource() << std::endl;
    printRecords("Postgres extract", pgConn.extract());
    std::cout << std::endl;

    // Test RestApiConnector
    RestApiConnector apiConn;
    std::cout << "RestAPI source: " << apiConn.getSource() << std::endl;
    printRecords("RestAPI extract", apiConn.extract());
    std::cout << std::endl;

    // Test CsvConnector
    CsvConnector csvConn;
    std::cout << "CSV source: " << csvConn.getSource() << std::endl;
    printRecords("CSV extract", csvConn.extract());
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "TEST 2: Testing Concrete Factories" << std::endl;
    std::cout << "========================================" << std::endl;

    // Test PostgresFactory
    PostgresFactory pgFactory;
    Connector *pgConnFromFactory = pgFactory.createConnector();
    std::cout << "PostgresFactory created connector with source: "
              << pgConnFromFactory->getSource() << std::endl;
    printRecords("PostgresFactory extract", pgConnFromFactory->extract());
    delete pgConnFromFactory;
    std::cout << std::endl;

    // RestApiFactory
    RestApiFactory apiFactory;
    Connector *apiConnFromFactory = apiFactory.createConnector();
    std::cout << "RestApiFactory created connector with source: "
              << apiConnFromFactory->getSource() << std::endl;
    printRecords("RestApiFactory extract", apiConnFromFactory->extract());
    delete apiConnFromFactory;
    std::cout << std::endl;

    // Test CsvFactory
    CsvFactory csvFactory;
    Connector *csvConnFromFactory = csvFactory.createConnector();
    std::cout << "CsvFactory created connector with source: "
              << csvConnFromFactory->getSource() << std::endl;
    printRecords("CsvFactory extract", csvConnFromFactory->extract());
    delete csvConnFromFactory;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "TEST 3: Polymorphic Behavior (THE ACTUAL PATTERN)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "The Pipeline will treat all factories as ConnectorFactory*" << std::endl;
    std::cout << std::endl;

    ConnectorFactory *factories[] = {
        new PostgresFactory(),
        new RestApiFactory(),
        new CsvFactory()};

    for (int i = 0; i < 3; ++i)
    {
        Connector *conn = factories[i]->createConnector();
        std::cout << "Factory " << i << " created connector with source: "
                  << conn->getSource() << std::endl;
        printRecords("  Extracted", conn->extract());

        delete conn;
    }

    for (int i = 0; i < 3; ++i)
    {
        delete factories[i];
    }

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "TEST COMPLETE" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}