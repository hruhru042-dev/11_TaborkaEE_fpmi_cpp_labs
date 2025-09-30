#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
void mySwap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}
int main() {
    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Invalid size!" << std::endl;
        return 1;
    }
    float* arr = new float[n];
    bool choice;
    std::cout << "How do you want to enter the array: randomly (enter 1) or by yourself (enter 0)? ";
    if (!(std::cin >> choice)) {
        std::cout << "Error, enter a number" << std::endl;
        delete[] arr;
        return 1;
    }
    if (choice == 1) {
        srand(static_cast<unsigned>(time(0)));
        float min_val, max_val;
        std::cout << "Enter minimum range limit: ";
        std::cin >> min_val;
        std::cout << "Enter maximum range limit: ";
        std::cin >> max_val;
        if (max_val < min_val) {
            float temp = max_val;
            max_val = min_val;
            min_val = temp;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(min_val, max_val);
        for (int i = 0; i < n; ++i) {
            arr[i] = dist(gen);
        }
    }
    else {
        for (int i = 0; i < n; ++i) {
            std::cout << "Element " << i + 1 << ": ";
            std::cin >> arr[i];
            if (!std::cin) {
                std::cout << "Error, enter a number" << std::endl;
                delete[] arr;
                return 1;
            }
        }
    }
    std::cout << "Your array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    int maxLength = 1; 
    int currentLength = 1; 
    for (int i = 1; i < n; ++i) {
        if (arr[i] >= arr[i - 1]) {
            ++currentLength; 
        }
        else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 1;
        }
    }
    if (currentLength > maxLength) {
        maxLength = currentLength;
    }
    std::cout << "Length of the longest ordered chain: " << maxLength << std::endl;
    int maxIdx = 0;
    int minIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (fabs(arr[i]) > fabs(arr[maxIdx])) {
            maxIdx = i;
        }
        if (fabs(arr[i]) < fabs(arr[minIdx])) {
            minIdx = i;
        }
    }
    int start = (maxIdx < minIdx) ? maxIdx : minIdx;
    int end = (maxIdx > minIdx) ? maxIdx : minIdx;
    float product = 1.0;
    if (start + 1 >= end) {
        std::cout << "No elements between max and min by absolute value." << std::endl;
    }
    else {
        for (int i = start + 1; i < end; ++i) {
            product *= arr[i];
        }
        std::cout << "The product of elements between the maximum and minimum in absolute value: " << product << std::endl;
    }
    for (int i = 0; i < n; i += 2) {
        for (int j = i + 2; j < n; j += 2) {
            if (arr[i] < arr[j]) {
                mySwap(arr[i], arr[j]);
            }
        }
    }
    for (int i = 1; i < n; i += 2) {
        for (int j = i + 2; j < n; j += 2) {
            if (arr[i] > arr[j]) {
                mySwap(arr[i], arr[j]);
            }
        }
    }
    std::cout << "New array: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    delete[] arr;
    return 0;
}
