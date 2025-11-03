
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cmath>
const int length = 1000;
const float EPSILON = 1e-6f;
void printArray(const float* arr, int size) {
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
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
void getIntLessThan1000(int value) {
    if (!(std::cin) || value >= 1000) {
        throw "Error: invalid integer input!";
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
int countUnique(const float* arr, int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        bool isUnique = true;
        for (int j = 0; j < i; ++j) {
            if (std::abs(arr[i] - arr[j]) < EPSILON) {
                isUnique = false;
                break;
            }
        }
        if (isUnique)
            ++count;
    }
    return count;
}
void sumBetweenNegatives(const float* arr, int size) {
    int first = -1, last = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < 0) {
            first = i;
            break;
        }
    }
    for (int i = size - 1; i >= 0; --i) {
        if (arr[i] < 0) {
            last = i;
            break;
        }
    }
    if (first == -1 || last == -1) {
        std::cout << "There are no negative elements.\n";
    }
    if (first == last) {
        std::cout << "There is only one negative element in the array.\n";
    }
    if (last - first == 1) {
        std::cout << "There are no other values between the first and last negative element.\n";
    }
    if (first >= 0 && last > first && last < size) {
        float sum = 0;
        for (int i = first + 1; i < last; ++i)
            sum += arr[i];
        std::cout << "Sum between first and last negative: " << sum << std::endl;
    }
}
void compressArray(float* arr, int size, float x) {
    int write_index = 0;
    for (int read_index = 0; read_index < size; ++read_index) {
        if (arr[read_index] >= -x && arr[read_index] <= x)
            arr[write_index++] = arr[read_index];
    }
    for (int i = write_index; i < size; ++i)
        arr[i] = 0;
}
int main() {
    float arr[length];
    try {
        int size;
        std::cout << "Enter size less than 1000: ";
        std::cin >> size;
        getIntLessThan1000(size);
        checkNegative(size);
        try {
            fillArray(arr, size);
            std::cout << "Your array: ";
            printArray(arr, size);
            int uniqueCount = countUnique(arr, size);
            std::cout << "Number of unique elements: " << uniqueCount << std::endl;
            sumBetweenNegatives(arr, size);
            int x;
            std::cout << "Enter number X: ";
            std::cin >> x;
            checkLetter();
            compressArray(arr, size, x);
            std::cout << "Compressed array: ";
            printArray(arr, size);
        }
        catch (const char* msg) {
            std::cout << msg;
            return 1;
        }
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}


