#pragma once
#include <memory>
#include <vector>
#include "../data/MarketDataLoader.h"
#include "ExecutionEngine.h"
#include "../strategies/Strategy.h"
#include "Portfolio.h"
using namespace std;
class Backtester {
public:
    Backtester(shared_ptr<MarketDataLoader> loader,
               vector<shared_ptr<Strategy>> strategies,
               shared_ptr<ExecutionEngine> engine,
               Portfolio& portfolio);

    void run();

private:
    shared_ptr<MarketDataLoader> loader;
    vector<shared_ptr<Strategy>> strategies;
    shared_ptr<ExecutionEngine> engine;
    Portfolio& portfolio;
};
