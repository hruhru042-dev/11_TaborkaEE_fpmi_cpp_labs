#include <iostream>
#include <random>
#include <ctime>
void mySwap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}
void printArray(const float arr[], int size) {
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
float absFloat(float x) {
    return (x < 0) ? -x : x;
}
int main() {
    int size;
    std::cout << "Enter size of array: ";
    std::cin >> size;
    if (size <= 0 || size > 1000000) {
        std::cout << "Invalid or too large size!" << std::endl;
        return 1;
    }
    float* arr = new float[size];
    int choice;
    std::cout << "How do you want to enter the array: randomly (enter 1) or by yourself (enter 0)? ";
    std::cin >> choice;
    switch (choice) {
    case 1: {
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
        for (int i = 0; i < size; ++i) {
            arr[i] = dist(gen);
        }
        break;
    }
    case 0: {
          for (int i = 0; i < size; ++i) {
              std::cout << "Element " << i + 1 << ": ";
              std::cin >> arr[i];
              if (!(std::cin)) {
                  std::cout << "Enter a number!" << std::endl;
                  std::cin.clear();
                  std::cin.ignore(10000, '\n');
                  --i; 
              }
          }
          break;
    }
    default:
        std::cout << "Enter 1 or 0" << std::endl;
            delete[] arr;
            return 1;
    }
    std::cout << "Your array: ";
    printArray(arr, size);
    std::cout << std::endl;
    int maxLength = 1; 
    int currentLength = 1; 
    for (int i = 1; i < size; ++i) {
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
    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (absFloat(arr[i]) > absFloat(arr[maxIdx]))
            maxIdx = i;
        if (absFloat(arr[i]) < absFloat(arr[minIdx]))
            minIdx = i;
    }
    int start = std::min(maxIdx, minIdx);
    int end = std::max(maxIdx, minIdx);
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
    for (int i = 0; i < size; i += 2) {
        for (int j = i + 2; j < size; j += 2) {
            if (arr[i] < arr[j]) {
                mySwap(arr[i], arr[j]);
            }
        }
    }
    for (int i = 1; i < size; i += 2) {
        for (int j = i + 2; j < size; j += 2) {
            if (arr[i] > arr[j]) {
                mySwap(arr[i], arr[j]);
            }
        }
    }
    std::cout << "New array: ";
    printArray(arr, size);
    delete[] arr;
    return 0;
}
