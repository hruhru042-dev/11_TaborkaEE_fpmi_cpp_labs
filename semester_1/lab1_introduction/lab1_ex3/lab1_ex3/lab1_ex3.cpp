
#include <iostream>

int main()
{
	int n, s = 0;
		std::cout << "enter n" << std::endl;
		std::cin >> n;
	if (n <= 0) {
		std::cout << "error";
		return 0;
	}
	if (n > 0) {
		for (int i = 1; i <= n; ++i) {
			s += i * i;
		}
	}
	std::cout << "s= " << s;
	return 0;
}
   