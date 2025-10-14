#pragma once
#include "Strategy.h"
#include <deque>

class MeanReversion : public Strategy {
private:
    std::deque<double> priceWindow;
    int windowSize;
    double threshold;

public:
    MeanReversion(int windowSize, double threshold);
    void onData(const std::string& timestamp, double price) override;
    std::vector<Order> generateSignals() override;
};
