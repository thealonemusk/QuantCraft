#pragma once
#include "Order.h"
#include "../data/MarketDataLoader.h"
#include "Trade.h"

class ExecutionEngine {
public:
    virtual ~ExecutionEngine() = default;
    virtual Trade executeOrder(const Order& order, const Bar& bar) = 0;
};
