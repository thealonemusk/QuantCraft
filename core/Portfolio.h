#pragma once
#include <unordered_map>
#include <string>
#include "Trade.h"
#include <iostream>
using namespace std;
class Portfolio {
private:
    double cash;
    unordered_map<string, int> positions;

public:
    Portfolio(double initial_cash);
    void updatePosition(const Trade& trade);
    double getCash() const;
    int getPosition(const string& symbol) const;
    void printState() const;
};
