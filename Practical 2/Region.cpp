#include "Region.h"

Region::Region(const std::string& name, double distance)
    : Map(name, distance)
{}

void Region::describe() const{
    std::cout << "Region: " << getName() << " (Population: " << getPopulation() << ")\n";
    for(auto c : this->children){
        c->describe();
    }
}

int Region::getPopulation() const{
    int total = 0;
    for(auto c : this->children){
        total += c->getPopulation();
    }

    return total;
}

void Region::growPopulation(int amount){
    if(amount < 0){
        std::cout << "Invalid amount. Population growth cannot be negative.\n";
        return;
    }

    int numOfChildren = getChildCount();

    if(numOfChildren == 0){
        std::cout << "There are no places in this region.\n";
        return;
    }

    // Divide the requested growth among the children
    int baseAmount = amount / numOfChildren;
    int remainder = amount % numOfChildren;

    for(int i = 0; i < numOfChildren; i++){
        int childAmount = baseAmount;

        // Give the remainder to the first few children
        if(i < remainder){
            childAmount++;
        }

        children[i]->growPopulation(childAmount);
    }

    std::cout << "Region: Population grew by " << amount << std::endl;
    describe();
}

void Region::decreasePopulation(int amount){
    if(amount < 0){
        std::cout << "Invalid amount. Population decrease cannot be negative.\n";
        return;
    }

    int numOfChildren = getChildCount();

    if(numOfChildren == 0){
        std::cout << "There are no places in this region.\n";
        return;
    }

    // getting the population before the operation
    int beforePopulation = getPopulation();

    // Divide the requested decrease among the children
    int baseAmount = amount / numOfChildren;
    int remainder = amount % numOfChildren;

    for(int i = 0; i < numOfChildren; i++){
        int childAmount = baseAmount;

        // Distribute the remainder
        if(i < remainder){
            childAmount++;
        }

        children[i]->decreasePopulation(childAmount);
    }

    int afterPopulation = getPopulation();
    int actualDecrease = beforePopulation - afterPopulation;

    std::cout << "Region: Population decreased by " << actualDecrease << std::endl;
    describe();
}

void Region::add(Map* child){
    if(child == nullptr){
        std::cout << "Invalid place\n";
        return;
    }

    this->children.push_back(child);
    std::cout << "Successfully added a place\n";
}

void Region::remove(Map* child){
    if(child == nullptr) return;

    if(getChildCount() <= 0){
        std::cout << "Place not found, region is empty\n";
        return;
    }

    int k = 0;
    for (int p = 0; p < getChildCount(); p++){        
        if(this->children[p] == child){
            Map* c = this->children[p];
            this->children.erase(this->children.begin() + p);                   
            delete c;

            k = 1;
            std::cout << "Successfully deleted a place\n";
            break;
        }
    }

    if(k == 0)
        std::cout << "Place not found\n";
}

Map* Region::getChild(int index) const{
    int size = getChildCount();
    if(size <= 0){
        //std::cout << "Place not found, region is empty\n";
        return nullptr;
    }

    if(index < 0 || index >= size){
        //std::cout << "Invalid index\n";
        return nullptr;
    }

    return this->children[index];
}

int Region::getChildCount() const{
    return this->children.size();
}

Region::~Region(){
    if(getChildCount() <= 0) return;

    for (int p = 0; p < getChildCount(); p++){
        Map* c = this->children[p];
        this->children.erase(this->children.begin() + p);                   
        delete c;

        p--;
    }
}
