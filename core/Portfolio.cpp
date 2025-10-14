#include "Portfolio.h"
using namespace std;
Portfolio::Portfolio(double initial_cash) : cash(initial_cash) {}

void Portfolio::updatePosition(const Trade& trade) {
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
    for (const auto& [symbol, qty] : positions) {
        cout << "Position [" << symbol << "]: " << qty << "\n";
    }
}
