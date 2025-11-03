#include <random>
#include <cmath>
#include <cstdlib>
#include <iostream>
void checkLetter() {
    if (!(std::cin)) {
        throw "Error, this is not a number";
    }
}
void checkNegative(int num) {
    if (num <= 0) {
        throw "Error, this is negative number\n";
    }
}
float getMinimumLimit() {
    float limit;
    std::cout << "Enter minimum range limit: ";
    std::cin >> limit;
    checkLetter();
    return limit;
}
float getMaximumLimit() {
    float limit;
    std::cout << "Enter maximum range limit: ";
    std::cin >> limit;
    checkLetter();
    return limit;
}
void printArray(const float* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void fillArrayRandom(float* arr, int size) {
    float min_val = getMinimumLimit();
    float max_val = getMaximumLimit();
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
        checkLetter();
    }
}
void fillArray(float* arr, int size) {
    int choice;
    std::cout << "How do you want to enter the array: randomly (1) or manually (0)? ";
    std::cin >> choice;
    checkLetter();
    switch (choice) {
    case 1:
        fillArrayRandom(arr, size);
        break;
    case 0:
        fillArrayManual(arr, size);
        break;
    default:
        throw "Error, enter 0 or 1\n";
    }
}
int findLongestNonDecreasing(const float* arr, int size) {
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
void computeProductBetweenExtremes(const float* arr, int size) {
    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (std::abs(arr[i]) > std::abs(arr[maxIdx])) {
            maxIdx = i;
        }
        if (std::abs(arr[i]) < std::abs(arr[minIdx])) {
            minIdx = i;
        }
    }
    if (maxIdx == minIdx) {
        std::cout << "Maximum and minimum absolute values are at the same index. No range to compute.\n";
        return;
    }
    int start = std::min(maxIdx, minIdx);
    int end = std::max(maxIdx, minIdx);
    if (end - start <= 1) {
        std::cout << "No elements between extremes.\n";
        return;
    }
    float product = 1.0f;
    for (int i = start + 1; i < end; ++i) {
        product *= arr[i];
    }
    std::cout << "Product between elements with min and max absolute value: " << product << std::endl;
}
void sortEvenOdd(float* arr, int size) {
    for (int i = 0; i < size; i += 2) {
        for (int j = i + 2; j < size; j += 2) {
            if (arr[i] <= arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
    for (int i = 1; i < size; i += 2) {
        for (int j = i + 2; j < size; j += 2) {
            if (arr[i] >= arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}
int main() {
    try {
        int size;
        std::cout << "Enter size of your array: ";
        std::cin >> size;
        checkLetter();
        checkNegative(size);
        float* arr = new float[size];
        try {
            fillArray(arr, size);
            std::cout << "Your array: ";
            printArray(arr, size);
            int longestChain = findLongestNonDecreasing(arr, size);
            std::cout << "Length of the longest ordered chain: " << longestChain << std::endl;
            computeProductBetweenExtremes(arr, size);
            sortEvenOdd(arr, size);
            std::cout << "New array: ";
            printArray(arr, size);
        }
        catch (const char* msg) {
            std::cout << msg;
            delete[] arr;
            return 1;
        }
        delete[] arr;
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}



