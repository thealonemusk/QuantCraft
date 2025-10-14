#pragma once
#include <string>

enum class OrderType { MARKET, LIMIT };
enum class Side { BUY, SELL };

struct Order {
    int id;
    std::string symbol;
    OrderType type;
    Side side;
    double price;
    int quantity;
    std::string timestamp;
};
