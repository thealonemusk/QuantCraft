#pragma once
#include <string>
#include "Order.h"
using namespace std;
struct Trade {
    string symbol;
    double price;
    int quantity;
    string timestamp;
    Side side;
};
