
#include <iostream>

int main()
{
	long long n, s = 0; //для больших значений n выражение n*n может быть очень большим и быть близким к бесконечности
		std::cout << "enter n" << std::endl; //поэтому сумма может выходитть за пределы значений типа данных
		std::cin >> n; //в таких случаях программа может выдавать неправильный ответ или inf
	if (n <= 0) {
		std::cout << "error";
		return 0;
	}
	if (n > 0) {
		for (long long i = 1; i <= n; ++i) {
			s += i * i;
		}
	}
	std::cout << "s= " << s;
	return 0;
}
   