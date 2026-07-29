#include "Connector.h"

Connector::Connector(const std::string &source) : source(source) {}

std::string Connector::getSource()
{
    return source;
}