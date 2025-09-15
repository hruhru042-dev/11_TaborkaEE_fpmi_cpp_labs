

#include <iostream>

int main()
{
	int n, s=0;
	std::cout << "enter n" << std::endl;
	std::cin >> n;
	if (n <= 0) {
		std::cout << "error";
	}
	if (n > 0) {
		for (int i = 1; i <= n; i += 2) {
			s += i;
		}
	}
	std::cout << "summa: " << s;
	return 0;
}
 

