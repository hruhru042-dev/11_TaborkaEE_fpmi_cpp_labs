#include <iostream>
using namespace std;

int main() {
	int n, counter, counter2, a;
	cout << "Enter number" << endl;
	cin >> n;
	counter = 0;
	a = 2;
	counter2 = 0;
	while (counter != n) {
		for (int i = 2; i <= a / 2; i++) { 
			if (a % i == 0) {
				counter2 += 1;
				break;
			}
		}
		if (counter2 == 0) {
			counter += 1;
			cout << a << " ";
		}
		counter2 = 0;
		a += 1;
	}
	return 0;
}