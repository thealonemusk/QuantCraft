#pragma once
#include <unordered_map>
#include <string>
#include "Trade.h"
#include <iostream>

class Portfolio {
private:
    double cash;
    std::unordered_map<std::string, int> positions;

public:
    Portfolio(double initial_cash);
    void updatePosition(const Trade& trade);
    double getCash() const;
    int getPosition(const std::string& symbol) const;
    void printState() const;
};
