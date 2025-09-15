

#include <iostream>

int main()
{
	int k, s1 = 1, s2 = 1;
	std::cout << "enter k" << std::endl;
	std::cin >> k;
	if (k <= 0) {
		std::cout << "error";
		return 0;
	}
	if (k > 0, k % 2 == 0) {
		for (int i = 2; i <= k; i = i + 2) {
			s1 *= i;
		}
		std::cout << "double factorial: " << s1;
		return 0;
	}
	if (k > 0, k % 2 == 1) {
		for (int t = 1; t <= k; t = t + 2) {
			s2 *= t;
		}
		std::cout << "double factorial: " << s2;
		return 0;
	}
	return 0;
}
