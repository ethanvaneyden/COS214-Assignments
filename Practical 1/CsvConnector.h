#ifndef CSVCON_H
#define CSVCON_H

#include "Connector.h"

class CsvConnector : public Connector {

    public:
    CsvConnector();
    vector<string> extract();

};

#endif