#include "Momentum.h"
#include <algorithm>
using namespace std;
Momentum::Momentum(int lookback, double threshold, int tradeSize)
    : lookback(lookback), threshold(threshold), tradeSize(tradeSize) {}

void Momentum::onData(const string& timestamp, double price) {
    lastTimestamp = timestamp;
    window.push_back(price);
    if (static_cast<int>(window.size()) > lookback) window.pop_front();
}

vector<Order> Momentum::generateSignals() {
    vector<Order> orders;
    if (static_cast<int>(window.size()) < lookback) return orders;

    double first = window.front();
    double last = window.back();
    double momentum = (last - first) / first; // normalized momentum

    if (momentum > threshold) {
        orders.push_back({0, "TEST", OrderType::MARKET, Side::BUY, last, tradeSize, lastTimestamp});
    } else if (momentum < -threshold) {
        orders.push_back({0, "TEST", OrderType::MARKET, Side::SELL, last, tradeSize, lastTimestamp});
    }

    return orders;
}
