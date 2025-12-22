#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
int safeInput() {
    int value;
    if (!(std::cin >> value)) {
        throw "Invalid input: expected integer.";
    }
    return value;
}
std::set<int> sieveEratosthenes(int N) {
    std::set<int> primes;
    for (int i = 2; i <= N; ++i) {
        primes.insert(i);
    }
    for (int p = 2; p <= std::sqrt(N); ++p) {
        if (primes.contains(p)) {
            std::erase_if(primes, [p](int x) {
                return x > p && x % p == 0;
                });
        }
    }
    return primes;
}
int main() {
    std::cout << "Enter number N: ";
    int N = safeInput();
    std::set<int> primes = sieveEratosthenes(N);
    std::cout << "Primes before " << N << ": ";
    for (std::set<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    return 0;
}
