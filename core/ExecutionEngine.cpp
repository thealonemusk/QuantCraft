#include "ExecutionEngine.h"
#include <random>

class SimpleExecutionEngine : public ExecutionEngine {
public:
    explicit SimpleExecutionEngine(double slippagePct = 0.0005) : slippage(slippagePct) {}

    Trade executeOrder(const Order& order, const Bar& bar) override {
        // Market fill at bar.close with slippage depending on side
        double price = bar.close;
        if (order.side == Side::BUY) price *= (1.0 + slippage);
        else price *= (1.0 - slippage);

        Trade t;
        t.symbol = order.symbol;
        t.price = price;
        t.quantity = order.quantity;
        t.timestamp = order.timestamp.empty() ? bar.timestamp : order.timestamp;
        t.side = order.side;
        return t;
    }

private:
    double slippage;
};
