

#include <iostream>

int main()
{
	long long n;
	std::cout << "Enter n:" << std::endl;
	std::cin >> n;
	long long l = 0;
	long long c = 1;
	if (n >= 1) {
		for (int i = 1; i <= n; ++i) {
			if (i % 2 == 0) {
				l += i;
			}
			else {
				c *= i;
			}
		}
		std::cout << "summa: " << l << std::endl;
		std::cout << "composition: " << c << std::endl;
	}
	
	long long s = 0;
	long long p = 1;
	if (n < 0) {
		for (int t = 1; t >= n; t= --t) {
			if (t % 2 == 0) {
				s += t;
			}
			else {
				p *= t;
			}
		}
		std::cout << "summa: " << s << std::endl;
		std::cout << "composition: " << p << std::endl;
	}
	
	return 0;
}