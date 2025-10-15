#include "Portfolio.h"

using namespace std;

Portfolio::Portfolio(double initial_cash) : cash(initial_cash) {}

bool Portfolio::applyTrade(const Trade& trade, double maxAllowedLeverage) {
    double notional = trade.price * trade.quantity;

    if (trade.side == Side::BUY) {
        // Basic risk check: allow buying only if resulting cash >= -maxAllowedLeverage * initial_cash
        // We approximate initial cash by maxAllowedLeverage factor relative to current cash for simplicity.
        double projectedCash = cash - notional;
        double allowedNegative = -abs(maxAllowedLeverage * 100000.0); // conservative placeholder
        if (projectedCash < allowedNegative) {
            return false;
        }
        cash = projectedCash;
        positions[trade.symbol] += trade.quantity;
        return true;
    } else {
        // SELL: allow even if it reduces position (permit shorting for now)
        cash += notional;
        positions[trade.symbol] -= trade.quantity;
        return true;
    }
}

void Portfolio::updatePosition(const Trade& trade) {
    // Legacy unconditional update
    if (trade.side == Side::BUY) {
        cash -= trade.price * trade.quantity;
        positions[trade.symbol] += trade.quantity;
    } else {
        cash += trade.price * trade.quantity;
        positions[trade.symbol] -= trade.quantity;
    }
}

double Portfolio::getCash() const {
    return cash;
}

int Portfolio::getPosition(const string& symbol) const {
    auto it = positions.find(symbol);
    return it != positions.end() ? it->second : 0;
}

void Portfolio::printState() const {
    cout << "Cash: " << cash << "\n";
    for (const auto& kv : positions) {
        cout << "Position [" << kv.first << "]: " << kv.second << "\n";
    }
}
