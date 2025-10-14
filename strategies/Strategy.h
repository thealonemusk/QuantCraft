#pragma once
#include "../core/Order.h"
#include <vector>
#include <string>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void onData(const std::string& timestamp, double price) = 0;
    virtual std::vector<Order> generateSignals() = 0;
};
