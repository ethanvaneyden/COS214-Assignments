#include "RunCheckpoint.h"
#include "Pipeline.h"
#include "CheckpointManager.h"
#include "PostgresConnector.h"
#include "RestApiConnector.h"
#include "RestApiFactory.h"
#include "CsvConnector.h"
#include "PostgresFactory.h"
#include "RestApiConnector.h"
#include "CsvFactory.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void checkPointTest();
void testSource();

int main()
{
    cout << "Please type the number of test - 1 (Test Source) 2 (Test Checkpoint):";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        testSource();
        break;
    case 2:
        checkPointTest();
        break;
    default:
        cout << "Please enter a valid number";
        break;
    }
}

void checkPointTest()
{
    cout << "Test 1: Run checkpoint" << "\n==================================";
    RunCheckpoint *checkpoint = new RunCheckpoint(2, {"a", "b", "c"});
    cout << "Stage is: " << checkpoint->getStage() << endl;
    cout << "Records size is: " << checkpoint->getRecords().size() << endl;
    delete checkpoint;

    cout << "Test 2: Checkpoint Manager" << "\n==================================" << endl;
    CheckpointManager *cpm = new CheckpointManager();
    RunCheckpoint *checkpoint1 = new RunCheckpoint(6, {"a", "b", "c"});
    RunCheckpoint *checkpoint2 = new RunCheckpoint(2, {"a", "c"});
    cpm->save(checkpoint1);
    cpm->save(checkpoint2);

    RunCheckpoint *last = cpm->undo();
    std::cout << "Last stage is now: " << last->getStage() << std::endl;

    delete last;
}

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

void testSource()
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
}
