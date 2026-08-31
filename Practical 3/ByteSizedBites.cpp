#include "ByteSizedBites.h"

ByteSizedBites::ByteSizedBites(EventComponent *parent)
    : EventLeaf("ByteSizedBites", parent), isOpen(false), TotalChairs(20), visitorsOnChairs(0),
      foodStock(50), drinkStock(50), snackStock(50), energyBarStock(25),
      staffCount(3), ordersInProgress(0), specialOfTheDay("No special today"),
      lastMessage("Normal operation") {}

void ByteSizedBites::update(const TechSignal &signal) {
    switch (signal.getType()) {
    case TechSignal::Type::UNKNOWN:
        lastMessage = "Unknown signal received";
        break;
    case TechSignal::Type::OPEN:
        open();
        break;
    case TechSignal::Type::CLOSE:
        close();
        break;
    case TechSignal::Type::RESUME:
        isOpen = true;
        lastMessage = "Resumed operation";
        break;
    case TechSignal::Type::FULL_CAPACITY:
        visitorsOnChairs = TotalChairs;
        lastMessage = "Reached full capacity";
        break;
    case TechSignal::Type::POWER_FAILURE:
        close();
        lastMessage = "Power failure";
        break;
    case TechSignal::Type::EMERGENCY_PAUSE:
        close();
        lastMessage = "Emergency pause";
        break;
    case TechSignal::Type::NETWORK_FAILURE:
        ordersInProgress = 0;
        lastMessage = "Network failure - active orders reset";
        break;
    case TechSignal::Type::SCHEDULE_CHANGE:
        lastMessage = "Schedule change: " + signal.getMessage();
        break;
    default:
        break;
    }
}

void ByteSizedBites::open() {
    isOpen = true;
    lastMessage = "Now open";
}

void ByteSizedBites::close() {
    isOpen = false;
    lastMessage = "Now closed";
}

std::string ByteSizedBites::getStatus() const {
    std::string stateStr = getName() + " | ";
    stateStr += (isOpen ? "OPEN" : "CLOSED") + std::string(" | Visitors: ");
    stateStr += std::to_string(visitorsOnChairs) + "/" + std::to_string(TotalChairs);
    stateStr += " | Stock [Food: " + std::to_string(foodStock) + ", Drink: " + std::to_string(drinkStock);
    stateStr += ", Snack: " + std::to_string(snackStock) + ", EnergyBar: " + std::to_string(energyBarStock) + "]";
    stateStr += " | Staff: " + std::to_string(staffCount) + " | Active Orders: " + std::to_string(ordersInProgress);
    stateStr += " | Special: " + specialOfTheDay;
    stateStr += " | Status: " + lastMessage;
    return "- " + stateStr + "\n";
}

int ByteSizedBites::getCapacity() const {
    return TotalChairs;
}

int ByteSizedBites::getCurrentVisitors() const {
    return visitorsOnChairs;
}

int ByteSizedBites::enterVisitor(int visitors) {
    if (visitors <= 0 || !isOpen) return 0;
    int space = TotalChairs - visitorsOnChairs;
    int admitted = (visitors < space) ? visitors : space;
    visitorsOnChairs += admitted;
    return admitted;
}

int ByteSizedBites::leaveVisitor(int visitors) {
    if (visitors <= 0) return 0;
    int removed = (visitors < visitorsOnChairs) ? visitors : visitorsOnChairs;
    visitorsOnChairs -= removed;
    return removed;
}

bool ByteSizedBites::getIsOpen() const { return isOpen; }
void ByteSizedBites::setIsOpen(bool status) { isOpen = status; }
int ByteSizedBites::getTotalChairs() const { return TotalChairs; }

void ByteSizedBites::setTotalChairs(int chairs) {
    if (chairs >= 0 && chairs >= visitorsOnChairs) {
        TotalChairs = chairs;
    }
}

int ByteSizedBites::getVisitorsOnChairs() const { return visitorsOnChairs; }

void ByteSizedBites::setVisitorsOnChairs(int visitors) {
    if (visitors >= 0 && visitors <= TotalChairs) {
        visitorsOnChairs = visitors;
    }
}

bool ByteSizedBites::seatVisitor() {
    if (!isOpen || visitorsOnChairs >= TotalChairs)
        return false;

    ++visitorsOnChairs;
    return true;
}

bool ByteSizedBites::removeVisitor() {
    if (visitorsOnChairs <= 0)
        return false;

    --visitorsOnChairs;
    return true;
}

int ByteSizedBites::getFoodStock() const { return foodStock; }
void ByteSizedBites::setFoodStock(int stock) { if (stock >= 0) foodStock = stock; }
int ByteSizedBites::getDrinkStock() const { return drinkStock; }
void ByteSizedBites::setDrinkStock(int stock) { if (stock >= 0) drinkStock = stock; }
int ByteSizedBites::getSnackStock() const { return snackStock; }
void ByteSizedBites::setSnackStock(int stock) { if (stock >= 0) snackStock = stock; }
int ByteSizedBites::getEnergyBarStock() const { return energyBarStock; }
void ByteSizedBites::setEnergyBarStock(int stock) { if (stock >= 0) energyBarStock = stock; }

bool ByteSizedBites::useFood(int amount) {
    if (amount <= 0 || amount > foodStock) return false;
    foodStock -= amount;
    return true;
}

bool ByteSizedBites::useDrink(int amount) {
    if (amount <= 0 || amount > drinkStock) return false;
    drinkStock -= amount;
    return true;
}

bool ByteSizedBites::useSnack(int amount) {
    if (amount <= 0 || amount > snackStock) return false;
    snackStock -= amount;
    return true;
}

bool ByteSizedBites::useEnergyBar(int amount) {
    if (amount <= 0 || amount > energyBarStock) return false;
    energyBarStock -= amount;
    return true;
}

int ByteSizedBites::getStaffCount() const { return staffCount; }
void ByteSizedBites::setStaffCount(int count) { if (count >= 0) staffCount = count; }
int ByteSizedBites::getOrdersInProgress() const { return ordersInProgress; }
void ByteSizedBites::setOrdersInProgress(int orders) { if (orders >= 0) ordersInProgress = orders; }

void ByteSizedBites::startOrder() {
    if (isOpen && staffCount > 0)
        ++ordersInProgress;
}

void ByteSizedBites::completeOrder() {
    if (ordersInProgress > 0)
        --ordersInProgress;
}

std::string ByteSizedBites::getSpecialOfTheDay() const { return specialOfTheDay; }
void ByteSizedBites::setSpecialOfTheDay(const std::string &special) { specialOfTheDay = special; }