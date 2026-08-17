#include "Region.h"

Region::Region(const std::string& name) : Map(name){
}

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
    // to make it fair, we
    // divide amount by num of children
    // then grow each child by that factor.
    // rounding up, when necessary

    int numOfChildren = this->getChildCount();

    if(numOfChildren == 0){
        //no inhabitants
        std::cout << "There are no inhabitants to grow\n";
    }
    else{
        int factor = amount / numOfChildren;

        //checking whether rounding is needed
        if(numOfChildren * factor != amount)
            factor++;       //rounding up by 1

        for(auto c : this->children){
            c->growPopulation(factor);
        }
        
        //getting total increase number
        factor *= numOfChildren;
        std::cout << "Region: Population grew by " << factor << std::endl;
    }

    describe();
}

void Region::decreasePopulation(int amount){
    // to make it fair, we
    // divide amount by num of children
    // then decrease each child by that factor.
    // rounding down, when necessary

    int numOfChildren = this->getChildCount();

    if(numOfChildren == 0){
        //no inhabitants
        std::cout << "There are no inhabitants to decrease\n";
    }
    else{
        int factor = amount / numOfChildren;       // also rounding down       

        for(auto c : this->children){
            c->decreasePopulation(factor);
        }
        
        //getting total increase number
        factor *= numOfChildren;
        std::cout << "Region: Population decreased by " << factor << std::endl;
    }

    describe();
}

void Region::add(Map* child){
    this->children.push_back(child);
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
            c = nullptr;
            child = nullptr;

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
        std::cout << "Place not found, region is empty\n";
        return nullptr;
    }

    if(index < 0 || index >= size){
        std::cout << "Invalid index\n";
        return nullptr;
    }

    return this->children[index];
}

int Region::getChildCount() const{
    return this->children.size();
}

Region::~Region(){
    if(getChildCount() <= 0) return;

    for (auto c : this->children){
        remove(c);
    }
}
