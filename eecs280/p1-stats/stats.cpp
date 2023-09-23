#include "stats.hpp"
#include "p1_library.hpp"
#include <vector>
#include <cmath>

using namespace std;

vector<pair<double, int> > summarize(vector<double> v) {
    vector<pair<double, int>> freq;
    sort(v);
    double curr = v[0];
    int sindex = 0;
    int i = 1;
    for (; i < v.size(); ++i) {
        if (v[i] != curr) {
            freq.push_back(pair<double, int>{curr, i - sindex});
            sindex = i;
            curr = v[i];
        }
    }
    freq.push_back(pair<double, int>{curr, i - sindex});
    return freq;
}

int count(vector<double> v) {
    return v.size();
}

double sum(vector<double> v) {
    double sum = 0;
    for (double &d: v) {
        sum += d;
    }
    return sum;
}

double mean(vector<double> v) {
    return sum(v) / count(v);
}

double median(vector<double> v) {
    sort(v);
    return count(v) % 2 == 0 ? (v[v.size() / 2] + v[v.size() / 2 - 1]) / 2 : v[v.size() / 2];
}

double mode(vector<double> v) {
    sort(v);
    double mode = v[0];
    int high = 1;
    double curr = v[0];
    int curri = 0;
    int i = 1;
    for (; i < v.size(); ++i) {
        if (v[i] != curr) {
            if (i - curri > high) {
                high = i - curri;
                mode = v[curri];
            }
            curr = v[i];
            curri = i;
        }
    }
    if (i - curri > high) {
        mode = v[curri];
    }
    return mode;
}

double min(vector<double> v) {
    // it is possible to do this by doing sort(v) and getting the first element
    // although it is more concise code, practically it has two problems:
    // 1. sorting is at least O(n log n) whereas iterating once through the vector is O(n)
    // 2. you would have to unnecessarily create a copy if you wanted to sort v
    double min = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] < min) {
            min = v[i];
        }
    }
    return min;
}

double max(vector<double> v) {
    // similar to min(vector<double>), iterating through the array once is better
    double max = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

static double square(const double& n) {
    return n * n;
}

static void stdevadj(double& val, const double &mean) {
    val = square(val - mean);
}

double stdev(vector<double> v) {
    double xbar = mean(v);
    for (double &val:v) {
        stdevadj(val, xbar);
    }
    return sqrt(sum(v) / (count(v) - 1));
}

double percentile(vector<double> v, double p) {
    if (p == 1) {
        return v[v.size() - 1];
    }
    sort(v);
    double n = p * (count(v) - 1) + 1;
    double whole = 0;
    double frac = modf(n, &whole);
    return v[whole - 1] + frac * (v[whole] - v[whole - 1]);
}
