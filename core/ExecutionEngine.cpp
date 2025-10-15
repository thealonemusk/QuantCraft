#include "ExecutionEngine.h"

using namespace std;

SimpleExecutionEngine::SimpleExecutionEngine(double slippagePct) : slippage(slippagePct) {}


Trade SimpleExecutionEngine::executeOrder(const Order& order, const Bar& bar) {
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

