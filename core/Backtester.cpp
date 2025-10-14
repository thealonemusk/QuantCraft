#include "Backtester.h"
#include <iostream>
using namespace std;
Backtester::Backtester(shared_ptr<MarketDataLoader> loader,
                       vector<shared_ptr<Strategy>> strategies,
                       shared_ptr<ExecutionEngine> engine,
                       Portfolio& portfolio)
    : loader(move(loader)), strategies(move(strategies)), engine(move(engine)), portfolio(portfolio) {}

void Backtester::run() {
    auto bars = loader->loadData();
    cout << "Loaded bars: " << bars.size() << "\n";
    for (const auto& bar : bars) {
        // feed price to each strategy
        for (auto& strat : strategies) {
            strat->onData(bar.timestamp, bar.close);
            auto orders = strat->generateSignals();
            for (const auto& o : orders) {
                auto trade = engine->executeOrder(o, bar);
                portfolio.updatePosition(trade);
                cout << "Executed trade: " << trade.symbol << " " << (trade.side==Side::BUY?"BUY":"SELL")
                          << " qty=" << trade.quantity << " price=" << trade.price << "\n";
            }
        }
    }
    cout << "Backtest completed. Portfolio:\n";
    portfolio.printState();
}
