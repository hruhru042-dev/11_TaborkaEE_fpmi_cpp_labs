#include <iostream>
#include "perfect.h"
int main() {
	try {
		int n;
		std::cout << "enter n" << std::endl;
		std::cin >> n;
		std::vector<int> perfect = findPerfectNumbers(n);
		for (int num = 0; num < perfect.size(); ++num) {
			std::cout << "perfect number <= n: " << perfect[num] << std::endl;
		}
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}