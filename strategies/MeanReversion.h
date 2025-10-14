#pragma once
#include "Strategy.h"
#include <deque>
using namespace std;
class MeanReversion : public Strategy {
private:
    deque<double> priceWindow;
    int windowSize;
    double threshold;

public:
    MeanReversion(int windowSize, double threshold);
    void onData(const string& timestamp, double price) override;
    vector<Order> generateSignals() override;
};
