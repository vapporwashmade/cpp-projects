#include <iostream>

int main() {
    int a = 5;
    std::cout << "address of a = " << &a << std::endl;
    int b = a;
    b = 7;
    std::cout << a << std::endl;
    int *p = &a;
    std::cout << p << '\t' << *p << std::endl;
    std::cout << "address of p = " << &p << std::endl;
    *p = 9;
    std::cout << "value of a = " << a << std::endl;
    return 0;
}
