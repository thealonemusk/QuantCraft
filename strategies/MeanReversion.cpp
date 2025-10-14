#include "MeanReversion.h"
#include <numeric>
#include <cmath>

MeanReversion::MeanReversion(int windowSize, double threshold)
    : windowSize(windowSize), threshold(threshold) {}

void MeanReversion::onData(const std::string& timestamp, double price) {
    priceWindow.push_back(price);
    if (priceWindow.size() > windowSize) {
        priceWindow.pop_front();
    }
}

std::vector<Order> MeanReversion::generateSignals() {
    std::vector<Order> signals;
    if (priceWindow.size() < windowSize) return signals;

    double mean = std::accumulate(priceWindow.begin(), priceWindow.end(), 0.0) / windowSize;
    double lastPrice = priceWindow.back();

    if (lastPrice < mean * (1 - threshold)) {
        signals.push_back({0, "TEST", OrderType::MARKET, Side::BUY, lastPrice, 10, "N/A"});
    } else if (lastPrice > mean * (1 + threshold)) {
        signals.push_back({0, "TEST", OrderType::MARKET, Side::SELL, lastPrice, 10, "N/A"});
    }

    return signals;
}
