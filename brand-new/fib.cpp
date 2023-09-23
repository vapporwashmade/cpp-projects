//
// Created by apoorv on 9/10/2023.
//

long fib(int n) {
    // requires n > 0
    int a = 1;
    int b = 1;
    for (int i = 1; i < n; ++i) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return a;
}
