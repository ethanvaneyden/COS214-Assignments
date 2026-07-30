#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <string>
#include <vector>

class Transformation{
    protected:
        std::string name;

    public:
        Transformation(std::string);
        Transformation* clone();
        std::vector<std::string> apply(std::vector<std::string>);
        std::string getName();
        ~Transformation();
};

#endif