
#include <iostream>
#include <random>
#include <ctime>
const int length = 1000;
void printArray(const float arr[], int size) {
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
int main() { 
    int size;
    float arr[length];  
    std::cout << "Enter size of array: ";
    std::cin >> size;
    if (size > length) {
        std::cout << "Size too large!" << std::endl;
        return 1;
    }
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
        std::cout << "Enter 1 or 0";
        delete[] arr;
        return 1;
    }
    std::cout << "Your array: ";
    printArray(arr, size);
    std::cout << std::endl;
    int uniqueCount = 0;
    for (int i = 0; i < size; ++i) {
        bool isUnique = true;
        for (int j = 0; j < i; ++j) {
            if ((arr[i] - arr[j]) < 0.000001 && (arr[i] - arr[j]) > -0.000001) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            ++uniqueCount;
        }
    }
    std::cout << "The number of different elements: " << uniqueCount << std::endl;
    int first_negative_idx = -1;
    int last_negative_idx = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < 0) {
            first_negative_idx = i;
            break;
        }
    }
    for (int i = size - 1; i >= 0; --i) {
        if (arr[i] < 0) {
            last_negative_idx = i;
            break;
        }
    }
    if (first_negative_idx != -1 && last_negative_idx != -1 && first_negative_idx < last_negative_idx) {
        float sum = 0;
        for (int i = first_negative_idx + 1; i < last_negative_idx; ++i) {
            sum += arr[i];
        }
        std::cout << "The sum of the elements between the first and last negative: " << sum << std::endl;
    }
    else {
        std::cout << "No negative elements found or there is only one";
    }
    int x;
    std::cout << "Enter number X ";
    std::cin >> x;
    int write_index = 0;
    for (int read_index = 0; read_index < size; ++read_index) {
        if ((arr[read_index] >= -x) && (arr[read_index] <= x)) {
            arr[write_index++] = arr[read_index];
        }
    }
    for (int i = write_index; i < size; ++i) {
        arr[i] = 0;
    }
    std::cout << "Compressed array: ";
    printArray(arr, size);
    return 0;
}

