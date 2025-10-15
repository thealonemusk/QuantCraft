#include "Backtester.h"
#include <iostream>
#include "ResultsAnalyzer.h"
using namespace std;

Backtester::Backtester(shared_ptr<MarketDataLoader> loader,
                       vector<shared_ptr<Strategy>> strategies,
                       shared_ptr<ExecutionEngine> engine,
                       Portfolio& portfolio,
                       shared_ptr<TradeLogger> logger)
    : loader(move(loader)), strategies(move(strategies)), engine(move(engine)), portfolio(portfolio), logger(move(logger)) {}

void Backtester::run() {
    auto bars = loader->loadData();
    cout << "Loaded bars: " << bars.size() << "\n";
    for (const auto& bar : bars) {
        for (auto& strat : strategies) {
            strat->onData(bar.timestamp, bar.close);
            auto orders = strat->generateSignals();
            for (const auto& o : orders) {
                auto trade = engine->executeOrder(o, bar);
                bool accepted = portfolio.applyTrade(trade);
                if (accepted) {
                    if (logger) logger->logTrade(trade);
                    cout << "Executed trade: " << trade.symbol << " " << (trade.side==Side::BUY?"BUY":"SELL")
                              << " qty=" << trade.quantity << " price=" << trade.price << "\n";
                } else {
                    cout << "Trade rejected by portfolio risk checks: " << trade.symbol << "\n";
                }
            }
        }
    }
    cout << "Backtest completed. Portfolio:\n";
    portfolio.printState();
    if (logger) {
        auto trades = logger->getTrades();
        auto results = ResultsAnalyzer::analyze(trades);
        cout << "Logged trades: realized PnL=" << results.realizedPnL << " maxDrawdown=" << results.maxDrawdown << "\n";
        logger->exportCSV("trades.csv");
    }
}
