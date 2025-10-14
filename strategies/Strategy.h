#pragma once
#include "../core/Order.h"
#include <vector>
#include <string>
using namespace std;
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void onData(const string& timestamp, double price) = 0;
    virtual vector<Order> generateSignals() = 0;
};
