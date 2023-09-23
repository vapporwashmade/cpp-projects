#include "stats.hpp"
#include "p1_library.hpp"
#include <iostream>

using namespace std;

int main() {
    string filename;
    string colname;
    cout << "enter a filename" << endl;
    cin >> filename;
    cout << "enter a column name" << endl;
    cin >> colname;
    cout << "reading column " << colname << " from " << filename << endl;
    vector data = extract_column(filename, colname);
    vector<pair<double, int>> summary = summarize(data);
    cout << "Summary (value: frequency)" << endl;
    for (pair<double, int> &p: summary) {
        cout << p.first << ": " << p.second << endl;
    }
    cout << endl;
    cout << "count = " << count(data) << endl;
    cout << "sum = " << sum(data) << endl;
    cout << "mean = " << mean(data) << endl;
    cout << "stdev = " << stdev(data) << endl;
    cout << "median = " << median(data) << endl;
    cout << "mode = " << mode(data) << endl;
    cout << "min = " << min(data) << endl;
    cout << "max = " << max(data) << endl;
    cout << "  0th percentile = " << percentile(data, 0) << endl;
    cout << " 25th percentile = " << percentile(data, 0.25) << endl;
    cout << " 50th percentile = " << percentile(data, 0.5) << endl;
    cout << " 75th percentile = " << percentile(data, 0.75) << endl;
    cout << "100th percentile = " << percentile(data, 1) << endl;
    return 0;
}