#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <vector>
#include <string>

using namespace std;

class Connector {
    public:
    Connector(const string&);
    virtual vector<string> extract() = 0;
    string getSource();
    virtual ~Connector();

    protected:
    string source;
};

#endif