#pragma once
#include <iostream>
#include <string>
using namespace std;
class Logger {
public:
    static void info(const string& msg) {
        cout << "[INFO] " << msg << endl;
    }
    static void error(const string& msg) {
        cerr << "[ERROR] " << msg << endl;
    }
};