#include "perfect.h"
std::vector<int> findPerfectNumbers(int n) {
	std::vector<int> result;
	for (int i = 6; i <= n; ++i) {
		int sum = 0;
		for (int t = 1; t <= i / 2; ++t) {
			if (i % t == 0) {
				sum += t;
			}
		}
		if (i == sum) {
			result.push_back(i);
		}
	}
	return result;
}