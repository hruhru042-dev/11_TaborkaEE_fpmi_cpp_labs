
#include <iostream>
#include <algorithm>
int main()
{
    int n, m;
    std::cout << "enter n" << std::endl;
    std::cin >> n;
    std::cout << "enter m" << std::endl;
    std::cin >> m;
    int min = std::min (n, m);
    std::cout << "common divisions " << n << ", " << m << std::endl;
    for (int i = 1; i <= min; ++i) {
        if (n % i == 0 && m % i == 0) {
            std::cout << i << " ";
        }
    }
    return 0;
}
