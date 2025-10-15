#pragma once
#include <vector>
#include "Trade.h"

struct Results {
    double realizedPnL{0.0};
    double maxDrawdown{0.0};
};

class ResultsAnalyzer {
public:
    static Results analyze(const std::vector<Trade>& trades);
};
