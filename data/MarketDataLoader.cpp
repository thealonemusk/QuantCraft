#include "MarketDataLoader.h"
#include "CSVParser.h"
#include <cstdlib>
#include <iostream>
using namespace std;
class CSVMarketDataLoader : public MarketDataLoader {
public:
    explicit CSVMarketDataLoader(const string& filename) : MarketDataLoader(filename) {}

    vector<Bar> loadData() const override {
        vector<Bar> bars;
        CSVParser parser(sourcePath);
        auto rows = parser.parse();
        for (const auto& r : rows) {
            // Expecting at least: timestamp, open, high, low, close, volume
            if (r.size() < 6) continue;
            Bar b;
            b.symbol = (r.size() >= 7 ? r[6] : "TEST");
            b.timestamp = r[0];
            try {
                b.open = stod(r[1]);
                b.high = stod(r[2]);
                b.low = stod(r[3]);
                b.close = stod(r[4]);
                b.volume = stod(r[5]);
            } catch (...) {
                // skip malformed row
                continue;
            }
            bars.push_back(b);
        }
        return bars;
    }
};
