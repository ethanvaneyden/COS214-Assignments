#include "Connector.h"

Connector::Connector(const string& source) : source(source) {}

string Connector::getSource() {
    return source;
}