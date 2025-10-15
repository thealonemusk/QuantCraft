#pragma once
#include "Order.h"
#include "../data/MarketDataLoader.h"
#include "Trade.h"
using namespace std;

class ExecutionEngine {
public:
    virtual ~ExecutionEngine() = default;
    virtual Trade executeOrder(const Order& order, const Bar& bar) = 0;
};

// SimpleExecutionEngine declaration - implemented in ExecutionEngine.cpp
class SimpleExecutionEngine : public ExecutionEngine {
public:
    explicit SimpleExecutionEngine(double slippagePct = 0.0005);
    Trade executeOrder(const Order& order, const Bar& bar) override;
private:
    double slippage;
};
