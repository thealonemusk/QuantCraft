#include "core/Portfolio.h"
#include "strategies/MeanReversion.h"
#include <iostream>

int main() {
    Portfolio portfolio(100000);
    MeanReversion strategy(20, 0.02);

    for (int i = 0; i < 100; ++i) {
        double price = 100 + (std::rand() % 10 - 5);
        strategy.onData("2020-01-01", price);
        auto signals = strategy.generateSignals();
        for (const auto& order : signals) {
            Trade trade = {order.symbol, order.price, order.quantity, order.timestamp, order.side};
            portfolio.updatePosition(trade);
        }
    }

    portfolio.printState();
    return 0;
}
