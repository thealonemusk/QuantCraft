#pragma once
#include <string>
using namespace std;
enum class OrderType { MARKET, LIMIT };
enum class Side { BUY, SELL };

struct Order {
    int id;
    string symbol;
    OrderType type;
    Side side;
    double price;
    int quantity;
    string timestamp;
};
