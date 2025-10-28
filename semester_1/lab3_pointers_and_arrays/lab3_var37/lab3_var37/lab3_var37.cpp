#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
void clearInput() {
    std::cin.clear();
    while (std::cin.get() != '\n');
}
int getValidSize() {
    int size;
    std::cout << "Enter size of array (1 to 1000000): ";
    std::cin >> size;
    if (!std::cin || size <= 0 || size > 1000000) {
        std::cout << "Error: invalid size!\n";
        clearInput();
        std::exit(1);
    }
    clearInput();
    return size;
}
int getChoice() {
    int choice;
    std::cout << "Choose input method — randomly (1) or manually (0): ";
    std::cin >> choice;
    if (!std::cin || (choice != 0 && choice != 1)) {
        std::cout << "Error: enter 0 or 1!\n";
        clearInput();
        std::exit(1);
    }
    clearInput();
    return choice;
}
float getValidFloat() {
    float value;
    std::cout << "Enter a float number: ";
    std::cin >> value;
    if (!std::cin) {
        std::cout << "Error: invalid float input!\n";
        clearInput();
        std::exit(1);
    }
    clearInput();
    return value;
}
void printArray(float* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void fillArrayRandom(float* arr, int size) {
    std::cout << "Enter minimum range limit: ";
    float min_val = getValidFloat();
    std::cout << "Enter maximum range limit: ";
    float max_val = getValidFloat();
    if (max_val < min_val) {
        std::swap(min_val, max_val);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min_val, max_val);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
}
void fillArrayManual(float* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << "Element " << i + 1 << ": ";
        std::cin >> arr[i];
        if (!std::cin) {
            std::cout << "Enter a valid number!\n";
            clearInput();
            --i;
        }
        else {
            clearInput();
        }
    }
}
int findLongestNonDecreasing(float* arr, int size) {
    int maxLength = 1, currentLength = 1;
    for (int i = 1; i < size; ++i) {
        if (arr[i] >= arr[i - 1])
            ++currentLength;
        else {
            maxLength = std::max(maxLength, currentLength);
            currentLength = 1;
        }
    }
    return std::max(maxLength, currentLength);
}
bool computeProductBetweenExtremes(float* arr, int size, float& product) {
    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (std::abs(arr[i]) > std::abs(arr[maxIdx])) {
            maxIdx = i;
        }
        if (std::abs(arr[i]) < std::abs(arr[minIdx])) {
            minIdx = i;
        }
    }
    int start = std::min(maxIdx, minIdx);
    int end = std::max(maxIdx, minIdx);
    if (start + 1 >= end) {
        std::cout << "no elements between extremes! \n";
    product = 1.0f;
    for (int i = start + 1; i < end; ++i) {
        product *= arr[i];
    }
    return true;
}
void sortEvenOdd(float* arr, int size) {
    for (int i = 0; i < size; i += 2) {
        for (int j = i + 2; j < size; j += 2) {
            if (arr[i] < arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
    for (int i = 1; i < size; i += 2) {
        for (int j = i + 2; j < size; j += 2) {
            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}
int main() {
    int size = getValidSize();
    float* arr = new float[size];
    int choice = getChoice();
    switch (choice) {
    case 1: {
        fillArrayRandom(arr, size);
        break;
    }
    case 0: {
        fillArrayManual(arr, size);
        break;
    }
    }
    std::cout << "Your array: ";
    printArray(arr, size);
    int longestChain = findLongestNonDecreasing(arr, size);
    std::cout << "Length of the longest ordered chain: " << longestChain << std::endl;
    float product;
    if (computeProductBetweenExtremes(arr, size, product)) {
        std::cout << "The product of elements between the maximum and minimum in absolute value: " << product << std::endl;
    }
    else {
        std::cout << "No elements between max and min by absolute value." << std::endl;
    }
    sortEvenOdd(arr, size);
    std::cout << "New array: ";
    printArray(arr, size);
    delete[] arr;
    return 0;
}





