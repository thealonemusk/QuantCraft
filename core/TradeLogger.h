#pragma once
#include <vector>
#include <string>
#include <mutex>
#include "Trade.h"
using namespace std;

class TradeLogger {
public:
    void logTrade(const Trade& t);
    // Export logged trades to CSV path. Returns true on success.
    bool exportCSV(const string& path) const;

    // Compute a simple realized PnL (sum of SELL proceeds - BUY costs)
    double realizedPnL() const;
    // Return a copy of logged trades
    vector<Trade> getTrades() const;

private:
    mutable mutex mtx;
    vector<Trade> trades;
};
