#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include "limitedDictionary.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc > 1) {
    freopen(argv[1], "r", stdin); // Redirect the standard input to a file
  }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Parse policy and capacity from stdin
    string policy_str;
    int capacity;
    if (!getline(cin, policy_str)) {
        cerr << "No policy provided\n";
        return 1;
    }
    if (!(cin >> capacity)) {
        cerr << "No capacity provided\n";
        return 1;
    }
    cin.ignore(); // ignore newline

    Policy policy = (policy_str == "fifo" ? FIFO : LRU);
    LimitedDictionary dict(capacity, policy);

    // Run commands
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string cmd;
        getline(ss, cmd, ',');

        if (cmd == "INS") {
            string key, value_str;
            getline(ss, key, ',');
            getline(ss, value_str, ',');
            Entry e{key, stoi(value_str)};
            dict.put(e);
        } 
        else if (cmd == "DEL") {
            string key;
            getline(ss, key, ',');
            dict.remove(key);
        } 
        else if (cmd == "FIND") {
            string key;
            getline(ss, key, ',');
            dict.get(key); // just exercises find
        }
    }

    // Dump final dictionary contents in array scan order
    for (auto &e : dict.dumpTable()) {
        cout << get<0>(e) << "," << get<1>(e) << "," << get<2>(e) << "\n";
    }

    return 0;
}

