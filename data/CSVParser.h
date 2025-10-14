#pragma once
#include <string>
#include <vector>
using namespace std;
class CSVParser {
public:
    explicit CSVParser(const string& filename);
    // Parses CSV and returns rows as vector of string vectors (cells)
    vector<vector<string>> parse() const;

private:
    string filename;
};
