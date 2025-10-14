
#include <iostream>
void Bubble(int a[], int size) {
	int i, j;
	int t;
	for (i = 0; i < size; ++i) {
		for (j = size - 1; j < i; --j) {
			if (a[j - 1] > a[j]) {
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;

			}
		}
	}
}
const int length = 1000;
int main(){
	int size;
	std::cout << "enter size " << std::endl;
	std::cin >> size;
	if (size > length) {
		std::cout << "Invalid size!";
		return 1;
	}
	int arr [length];
	std::cout << "enter elements" << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cin >> arr[i];
	}
	Bubble(arr, size);
	std::cout << "Your array: " << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i];
	}
	return 0;
}


