#pragma once
#include "Strategy.h"
#include <deque>
#include <vector>
using namespace std;
class Momentum : public Strategy {
public:
    Momentum(int lookback, double threshold, int tradeSize = 10);
    void onData(const string& timestamp, double price) override;
    vector<Order> generateSignals() override;

private:
    int lookback;
    double threshold;
    int tradeSize;
    deque<double> window;
    string lastTimestamp;
};
