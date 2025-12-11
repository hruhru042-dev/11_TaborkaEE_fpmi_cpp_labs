#include <iostream>
#include "perfect.h"
int main() {
	try {
		int n;
		std::cout << "enter positive n" << std::endl;
		std::cin >> n;
		if (!std::cin) throw "this is not a number!";
		if (n <= 0) throw "enter a positive number!";
		std::vector<int> perfect = findPerfectNumbers(n);
		if (perfect.empty()) throw "there is no perfect numbers <= n";
		std::cout << "perfect numbers <= n: ";
		for (int num = 0; num < perfect.size(); num++) {
			std::cout << perfect[num] << ", ";
		}
		std::cout << std::endl;
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}