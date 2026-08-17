#include "Map.h"

Map::Map(const std::string& name) : name(name){
}

void Map::add(Map* child){
    //base implementation as location doesn't have children
    //nothing to add
}

void Map::remove(Map* child){
    //base implementation as location doesn't have children
    //nothing to remove
}
        
std::string Map::getName() const{
    return this->name;
}
Map* Map::getChild(int index) const{
    //base implementation as location doesn't have children
    return nullptr;
}
int Map::getChildCount() const{
    //base implementation as location doesn't have children
    return 0;
}

Map::~Map(){
    //Nothing to delete,,,
}