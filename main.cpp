#include "core/Portfolio.h"
#include "strategies/MeanReversion.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include "utils/Logger.h"
using namespace std;
namespace MathUtils {
    inline double mean(const vector<double>& v) {
        if (v.empty()) return 0.0;
        return accumulate(v.begin(), v.end(), 0.0) / v.size();
    }
    inline double stddev(const vector<double>& v) {
        double m = mean(v);
        double accum = 0.0;
        for (double x : v) accum += (x - m) * (x - m);
        return v.empty() ? 0.0 : sqrt(accum / v.size());
    }
}

int main() {
    Portfolio portfolio(100000);
    MeanReversion strategy(20, 0.02);

    for (int i = 0; i < 100; ++i) {
        double price = 100 + (rand() % 10 - 5);
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
