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
    explicit Portfolio(double initial_cash);

    // Try to apply a trade. Returns true if accepted/applied, false if rejected
    // (e.g. insufficient cash or risk rules). This keeps callers aware of failures.
    bool applyTrade(const Trade& trade, double maxAllowedLeverage = 10.0);

    // Legacy - applies a trade unconditionally (kept for compatibility but not used)
    void updatePosition(const Trade& trade);

    double getCash() const;
    int getPosition(const string& symbol) const;
    void printState() const;
};
