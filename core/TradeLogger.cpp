#include "TradeLogger.h"
#include <fstream>
#include <numeric>
using namespace std;

void TradeLogger::logTrade(const Trade& t) {
    lock_guard<mutex> lk(mtx);
    trades.push_back(t);
}

bool TradeLogger::exportCSV(const std::string& path) const {
    lock_guard<mutex> lk(mtx);
    ofstream out(path);
    if (!out.is_open()) return false;
    out << "timestamp,symbol,side,price,quantity\n";
    for (const auto& t : trades) {
        out << t.timestamp << "," << t.symbol << "," << (t.side==Side::BUY?"BUY":"SELL")
            << "," << t.price << "," << t.quantity << "\n";
    }
    return true;
}

double TradeLogger::realizedPnL() const {
    lock_guard<mutex> lk(mtx);
    double pnl = 0.0;
    for (const auto& t : trades) {
        if (t.side == Side::SELL) pnl += t.price * t.quantity;
        else pnl -= t.price * t.quantity;
    }
    return pnl;
}

vector<Trade> TradeLogger::getTrades() const {
    lock_guard<mutex> lk(mtx);
    return trades;
}
