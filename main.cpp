#include "core/Portfolio.h"
#include "core/Backtester.h"
#include "core/ExecutionEngine.h"
#include "core/TradeLogger.h"
#include "data/MarketDataLoader.h"
#include "strategies/Momentum.h"
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // Adjust this path to point to a CSV file with timestamp,open,high,low,close,volume[,symbol]
    string csvPath = "data/sample.csv";

    auto loader = make_shared<CSVMarketDataLoader>(csvPath);
    vector<shared_ptr<Strategy>> strategies;
    strategies.push_back(make_shared<Momentum>(20, 0.01, 5));

    auto engine = make_shared<SimpleExecutionEngine>(0.0005);
    Portfolio portfolio(100000.0);
    auto logger = make_shared<TradeLogger>();

    Backtester bt(loader, strategies, engine, portfolio, logger);
    bt.run();

    return 0;
}
