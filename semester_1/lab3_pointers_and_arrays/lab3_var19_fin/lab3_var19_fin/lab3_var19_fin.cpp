
#include <iostream>
#include <random>
#include <ctime>
#include <set>
#include <cmath>
const int length = 1000;
int main(){
    int n;
    float arr[length];  
    std::cout << "Enter size of array: ";
    if (!(std::cin >> n) || (n<=0)) {
        std::cout << "Input error, enter non negative integer number " << std::endl;
        return 1;
    }
    if (n > length) {
        std::cout << "Size too large!" << std::endl;
        return 1;
    }
    bool choice;
    std::cout << "How do you want to enter the array: randomly (enter 1) or by yourself (enter 0)? ";
    if (!(std::cin >> choice)) {
        std::cout << "Error, enter a number" << std::endl;
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
        std::mt19937 gen(45218965);
        std::uniform_real_distribution<double>
            dist(min_val, max_val);
        for (int i = 0; i < n; ++i) {
            arr[i] = dist(gen);
        }
        std::cout << "Your array: ";
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        for (int i = 0; i < n; ++i) {
            std::cout << "Element " << i + 1 << ": ";
            std::cin >> arr[i];
            if (!(std::cin)) {
                std::cout << "Error, enter a number" << std::endl;
                break;
            }
        }
        std::cout << "Your array: ";
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    std::set<float> unique;
    for (int i = 0; i < n; ++i) {
        unique.insert(arr[i]);
    }
    std::cout << "The number of different elements: " << unique.size() << std::endl;
    int first_negative_idx = -1;
    int last_negative_idx = -1;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            first_negative_idx = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; --i) {
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
    for (int read_index = 0; read_index < n; ++read_index) {
        if (std::fabs(arr[read_index]) <= x) {
            arr[write_index++] = arr[read_index];
        }
    }
    for (int i = write_index; i < n; ++i) {
        arr[i] = 0;
    }
    std::cout << "Compressed array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

