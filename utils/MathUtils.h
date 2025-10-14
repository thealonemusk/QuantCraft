#pragma once
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;
namespace MathUtils {
    inline double mean(const vector<double>& v) {
        if (v.empty()) return 0.0;
        return accumulate(v.begin(), v.end(), 0.0) / static_cast<double>(v.size());
    }

    inline double stddev(const vector<double>& v) {
        if (v.size() < 2) return 0.0;
        double m = mean(v);
        double acc = 0.0;
        for (double x : v) {
            double d = x - m;
            acc += d * d;
        }
        return sqrt(acc / static_cast<double>(v.size() - 1));
    }
}
