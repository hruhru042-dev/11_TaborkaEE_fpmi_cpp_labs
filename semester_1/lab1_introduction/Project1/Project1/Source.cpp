#include <iostream>
using namespace std;

int main() {
	int n, chislo, obratnoe;
	cout << "Enter number" << endl;
	cin >> n;
	chislo = n;
	while (chislo != 0) {
		int last_digit = chislo % 10;
		obratnoe = obratnoe * 10 + last_digit;
		chislo /= 10;
	}
	if (chislo == obratnoe) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
	return 0;
}