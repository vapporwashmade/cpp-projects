/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

void test_sum_small_data_set();

void allsimple();

void edge_cases();

// Add prototypes for you test functions here.

int main() {
    test_sum_small_data_set();
    // Call your test functions here
    allsimple();
    edge_cases();
    return 0;
}

void test_sum_small_data_set() {
    cout << "test_sum_small_data_set" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);

    assert(sum(data) == 6);

    cout << "PASS!" << endl;
}

// Add the test function implementations here.
// simple tests -- one function because same dataset
void allsimple() {
    vector<double> data{17.7, 15.4, 5.2, 7.4, 10.0, 16.2, 4.5, 15.9, 9.2, 16.6, 9.2, 8.8, 13.5, 8.4, 17.4, 17.6, 10.0,
                        10.0, 11.2, 16.2};

    cout << "simple summarize test" << endl;

    vector<pair<double, int>> expected{
            {4.5,  1},
            {5.2,  1},
            {7.4,  1},
            {8.4,  1},
            {8.8,  1},
            {9.2,  2},
            {10,   3},
            {11.2, 1},
            {13.5, 1},
            {15.4, 1},
            {15.9, 1},
            {16.2, 2},
            {16.6, 1},
            {17.4, 1},
            {17.6, 1},
            {17.7, 1}
    };
    vector<pair<double, int>> actual = summarize(data);
    assert(actual == expected);

    cout << "PASSED" << endl;

    cout << "simple count test" << endl;
    assert(count(data) == 20);
    cout << "PASSED" << endl;

    cout << "simple sum test" << endl;
    assert(sum(data) == 240.4);
    cout << "PASSED" << endl;

    cout << "simple mean test" << endl;
    assert(mean(data) == 12.02);
    cout << "PASSED" << endl;

    cout << "simple median test" << endl;
    assert(median(data) == 10.6);
    cout << "PASSED" << endl;

    cout << "simple mode test" << endl;
    assert(mode(data) == 10.0);
    cout << "PASSED" << endl;

    cout << "simple min test" << endl;
    assert(min(data) == 4.5);
    cout << "PASSED" << endl;

    cout << "simple max test" << endl;
    assert(max(data) == 17.7);
    cout << "PASSED" << endl;
}

// edge cases
void summarize_edge() {
    cout << "edge case tests for summarize" << endl;
    assert((summarize(vector<double>{0}) == vector{pair<double, int>{0, 1}}));
    assert((summarize(vector<double>{0, 0}) == vector{pair<double, int>{0, 2}}));
    cout << "PASSED" << endl;
}

void count_edge() {
    cout << "edge case tests for count" << endl;
    assert(count(vector<double>{}) == 0);
    cout << "PASSED" << endl;
}

void sum_edge() {
    cout << "edge case tests for sum" << endl;
    assert(sum(vector<double>{2}) == 2);
    cout << "PASSED" << endl;
}

void mean_edge() {
    cout << "edge case tests for mean" << endl;
    assert(mean(vector<double>{0}) == 0);
    cout << "PASSED" << endl;
}

void median_edge() {
    cout << "edge case tests for median" << endl;
    assert(median(vector<double>{10}) == 10);
    assert(median(vector<double>{2, 2, 1}) == 2);
    cout << "PASSED" << endl;
}

void mode_edge() {
    cout << "edge case tests for mode" << endl;
    assert(mode(vector<double>{0}) == 0);
    assert(mode(vector<double>{1, 0}) == 0);
    cout << "PASSED" << endl;
}

void minmax_edge() {
    cout << "edge case tests for min and max" << endl;
    assert(min(vector<double>{0}) == 0);
    assert(max(vector<double>{0}) == 0);
    cout << "PASSED" << endl;
}

void stdev_edge() {
    cout << "edge case tests for stdev" << endl;
    assert(stdev(vector<double>{0, 0}) == 0);
    cout << "PASSED" << endl;
}

void percentile_edge() {
    cout << "edge case tests for percentile" << endl;
    assert(percentile(vector<double>{2}, 0) == 2);
    assert(percentile(vector<double>{2}, 1) == 2);
    assert(percentile(vector<double>{0, 2}, 0) == 0);
    assert(percentile(vector<double>{0, 2}, 1) == 2);
    cout << "PASSED" << endl;
}

void edge_cases() {
    summarize_edge();
    count_edge();
    sum_edge();
    mean_edge();
    median_edge();
    median_edge();
    mode_edge();
    minmax_edge();
    stdev_edge();
    percentile_edge();
}