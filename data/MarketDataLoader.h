#pragma once
#include <string>
#include <vector>
using namespace std;
struct Bar {
    string symbol;
    string timestamp;
    double open{0};
    double high{0};
    double low{0};
    double close{0};
    double volume{0};
};

class MarketDataLoader {
public:
    explicit MarketDataLoader(string source) : sourcePath(move(source)) {}
    virtual ~MarketDataLoader() = default;
    virtual vector<Bar> loadData() const = 0;

protected:
    string sourcePath;
};
