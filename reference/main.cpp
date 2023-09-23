#include <iostream>
#include <vector>

using namespace std;

void adj(int &val);

int main() {
    vector<int> a{4, 4, 1, 4, 64, 43, 6, 8, 5};
    for (int &val:a) {
        adj(val);
    }
    for (int val:a) {
        cout << val << endl;
    }
    return 0;
}

void adj(int &val) {
    val *= 2;
}