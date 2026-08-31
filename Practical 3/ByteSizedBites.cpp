#include "ByteSizedBites.h"

ByteSizedBites::ByteSizedBites(std::string name)
    : EventLeaf(name), isOpen(false), TotalChairs(20), visitorsOnChairs(0), foodStock(50), drinkStock(50), snackStock(50), energyBarStock(25), staffCount(3), ordersInProgress(0), specialOfTheDay("No special today")
{}

void ByteSizedBites::update(const TechSignal& signal){

}

void ByteSizedBites::open(){
    isOpen = true;
}

void ByteSizedBites::close(){
    isOpen = false;
}

std::string ByteSizedBites::getStatus() const{
    if (isOpen){
        return "ByteSizedBites is open. Visitors: " + std::to_string(visitorsOnChairs) + "/" + std::to_string(TotalChairs);
    }

    return "ByteSizedBites is closed.";
}

int ByteSizedBites::getCapacity() const{
    return TotalChairs;
}

bool ByteSizedBites::getIsOpen() const{
    return isOpen;
}

void ByteSizedBites::setIsOpen(bool status){
    isOpen = status;
}

// Seating
int ByteSizedBites::getTotalChairs() const{
    return TotalChairs;
}

void ByteSizedBites::setTotalChairs(int chairs){
    if (chairs >= 0 && chairs >= visitorsOnChairs){
        TotalChairs = chairs;
    }
}

int ByteSizedBites::getVisitorsOnChairs() const{
    return visitorsOnChairs;
}

void ByteSizedBites::setVisitorsOnChairs(int visitors){
    if (visitors >= 0 && visitors <= TotalChairs){
        visitorsOnChairs = visitors;
    }
}

bool ByteSizedBites::seatVisitor(){
    if (!isOpen)
        return false;

    if (visitorsOnChairs >= TotalChairs)
        return false;

    ++visitorsOnChairs;
    return true;
}

bool ByteSizedBites::removeVisitor(){
    if (visitorsOnChairs <= 0)
        return false;

    --visitorsOnChairs;
    return true;
}

int ByteSizedBites::getFoodStock() const{
    return foodStock;
}

void ByteSizedBites::setFoodStock(int stock){
    if (stock >= 0)
        foodStock = stock;
}

int ByteSizedBites::getDrinkStock() const{
    return drinkStock;
}

void ByteSizedBites::setDrinkStock(int stock){
    if (stock >= 0){
        drinkStock = stock;
    }
}

int ByteSizedBites::getSnackStock() const{
    return snackStock;
}

void ByteSizedBites::setSnackStock(int stock){
    if (stock >= 0)
        snackStock = stock;
}

int ByteSizedBites::getEnergyBarStock() const{
    return energyBarStock;
}

void ByteSizedBites::setEnergyBarStock(int stock){
    if (stock >= 0)    
        energyBarStock = stock;
}

bool ByteSizedBites::useFood(int amount){
    if (amount <= 0 || amount > foodStock){
        return false;
    }

    foodStock -= amount;
    return true;
}

bool ByteSizedBites::useDrink(int amount){
    if (amount <= 0 || amount > drinkStock)
        return false;

    drinkStock -= amount;
    return true;
}

bool ByteSizedBites::useSnack(int amount){
    if (amount <= 0 || amount > snackStock)
        return false;

    snackStock -= amount;
    return true;
}

bool ByteSizedBites::useEnergyBar(int amount){
    if (amount <= 0 || amount > energyBarStock)
        return false;

    energyBarStock -= amount;
    return true;
}

int ByteSizedBites::getStaffCount() const{
    return staffCount;
}

void ByteSizedBites::setStaffCount(int count){
    if (count >= 0)
        staffCount = count;
}

int ByteSizedBites::getOrdersInProgress() const{
    return ordersInProgress;
}

void ByteSizedBites::setOrdersInProgress(int orders){
    if (orders >= 0)
        ordersInProgress = orders;
}

void ByteSizedBites::startOrder(){
    if (isOpen && staffCount > 0)
        ++ordersInProgress;
}

void ByteSizedBites::completeOrder(){
    if (ordersInProgress > 0)
        --ordersInProgress;
}

std::string ByteSizedBites::getSpecialOfTheDay() const{
    return specialOfTheDay;
}

void ByteSizedBites::setSpecialOfTheDay(const std::string& special){
    specialOfTheDay = special;
}
