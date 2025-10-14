#pragma once
#include <string>
#include "Order.h"

struct Trade {
    std::string symbol;
    double price;
    int quantity;
    std::string timestamp;
    Side side;
};
