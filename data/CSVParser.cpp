#include "CSVParser.h"
#include <fstream>
#include <sstream>
using namespace std;
CSVParser::CSVParser(const string& filename) : filename(filename) {}

vector<vector<string>> CSVParser::parse() const {
    vector<vector<string>> rows;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if (!row.empty()) rows.push_back(row);
    }
    return rows;
}