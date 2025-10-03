#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "limitedDictionary.cpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
    string tests_folder = "tests";

    for (auto &entry : fs::directory_iterator(tests_folder)) {
        if (!entry.is_directory()) continue;
        string test_dir = entry.path().string();

        ifstream fin(test_dir + "/input.txt");
        if (!fin.is_open()) {
            cerr << "Could not open " << test_dir << "/input.txt\n";
            continue;
        }

        // Parse policy and capacity
        string policy_str;
        int capacity;
        getline(fin, policy_str);
        fin >> capacity;
        fin.ignore();

        Policy policy = (policy_str == "fifo" ? FIFO : LRU);
        LimitedDictionary dict(capacity, policy);

        // Run commands
        string line;
        while (getline(fin, line)) {
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
            } else if (cmd == "DEL") {
                string key;
                getline(ss, key, ',');
                dict.remove(key);
            } else if (cmd == "FIND") {
                string key;
                getline(ss, key, ',');
                dict.get(key);
            }
        }
        fin.close();

        // Write results into output.txt in same folder
        string result_file = test_dir + "/output.txt";
        ofstream fout(result_file);
        for (auto &e : dict.dumpTable()) {
            fout << get<0>(e) << "," << get<1>(e) << "," << get<2>(e) << "\n";
        }
        fout.close();

        //cout << "Wrote results to " << result_file << endl;
    }

    return 0;
}

