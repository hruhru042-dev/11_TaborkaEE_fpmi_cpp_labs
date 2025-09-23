#include <iostream>


int main() {

    int a, b, p, q;
    std::cout << "Enter two integers a and b: ";
    std::cin >> a >> b;
    p = a / b;
    q = a % b;
    std::cout << "p = " << p << ", q = " << q << '\n';

    return 0;
}