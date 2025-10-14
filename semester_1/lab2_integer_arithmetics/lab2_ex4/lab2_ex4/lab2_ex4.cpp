

#include <iostream>

int main()
{
    int n;
    std::cout << "enter n\n";
    std::cin >> n;
    for (int i = 6; i <= n; ++i) {
        int sum = 0;
        for (int t = 1; t <= i / 2; ++t) {
            if (i % t == 0) {
                sum += t;
            }
        }
        if (i == sum) {
            std::cout << "perfect number <= n: " << i << std::endl;
        }
    }
    return 0;
}

