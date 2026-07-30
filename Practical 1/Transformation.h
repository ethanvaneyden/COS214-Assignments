#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <string>
#include <vector>

class Transformation{
    protected:
        std::string name;

    public:
        Transformation(std::string);
        virtual Transformation* clone() = 0;
        virtual std::vector<std::string> apply(std::vector<std::string>) = 0;
        std::string getName();
        virtual ~Transformation();
};

#endif