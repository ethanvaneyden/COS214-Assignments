#ifndef REGION_H
#define REGION_H

#include "Map.h"
#include <vector>

class Region : public Map {
    private:
        std::vector<Map*> children;  // OWNED by this Region

    public:
        Region(const std::string& name);
        
        void describe() const override;
        int getPopulation() const override;
        
        // Composite operations
        void add(Map* child) override;
        void remove(Map* child) override;
        Map* getChild(int index) const override;
        int getChildCount() const override;

        // The Region OWNS its children. When the Region dies,
        // it must delete all its children to prevent memory leaks.
        ~Region() override;
};

#endif