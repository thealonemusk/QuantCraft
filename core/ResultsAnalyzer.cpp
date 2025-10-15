#include "ResultsAnalyzer.h"

using namespace std;

Results ResultsAnalyzer::analyze(const vector<Trade>& trades) {
    Results r;
    double equity = 0.0;
    double peak = 0.0;
    double maxDD = 0.0;

    for (const auto& t : trades) {
        if (t.side == Side::SELL) equity += t.price * t.quantity;
        else equity -= t.price * t.quantity;

        if (equity > peak) peak = equity;
        double dd = peak - equity;
        if (dd > maxDD) maxDD = dd;
    }

    r.realizedPnL = equity;
    r.maxDrawdown = maxDD;
    return r;
}
