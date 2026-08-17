#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
    private:
        std::string name;

    protected:
        Map(const std::string& name);

    public:        
        // Describes this place (recursive for Region)
        virtual void describe() const = 0;
        
        // (recursive for Region)
        virtual int getPopulation() const = 0;

        // Composite operations
        virtual void add(Map* child);
        virtual void remove(Map* child);
        
        virtual std::string getName() const;
        virtual Map* getChild(int index) const;
        virtual int getChildCount() const;

        virtual ~Map();
};

#endif