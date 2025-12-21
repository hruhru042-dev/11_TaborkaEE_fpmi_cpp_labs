#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <limits> 
void checkEmpty(std::vector<int>& v) {
    if (v.empty()) {
        throw "Vector is empty. Nothing to process";
    }
}
std::vector<int> inputVector() {
    std::vector<int> v;
    std::cout << "Enter elements of vector (Ctrl+D/Ctrl+Z for ending):\n";
    int n;
    while (std::cin >> n) {
        v.push_back(n);
    }
    return v;
}
int safeInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    if (!(std::cin >> value)) {
        throw "Invalid input: expected integer.";
    }
    return value;
}
void printVector(const std::vector<int>& v, const std::string& msg = "Vector") {
    std::cout << msg << ": ";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}
long long sumVector(const std::vector<int>& v) {
    return std::accumulate(v.begin(), v.end(), 0LL);
}
void replaceZerosWithAverage(std::vector<int>& v) {
    long long sum = sumVector(v);
    int avg = sum / (int)v.size();
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == 0) {
            v[i] = avg;
        }
    }
}
int countGreaterThan(const std::vector<int>& v, int p) {
    return std::count_if(v.begin(), v.end(), [&](int n) { return n > p; });
}
int countEqualTo(const std::vector<int>& v, int m) {
    return std::count(v.begin(), v.end(), m);
}
void replaceEvenAbsWithDiff(std::vector<int>& v) {
    int minVal = *std::min_element(v.begin(), v.end());
    int maxVal = *std::max_element(v.begin(), v.end());
    int diff = maxVal - minVal;
    for (size_t i = 0; i < v.size(); ++i) {
        if (std::abs(v[i]) % 2 == 0) {
            v[i] = diff;
        }
    }
}
void eraseDuplicatesByAbs(std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = i + 1; j < v.size(); ) {
            if (std::abs(v[j]) == std::abs(v[i])) {
                v.erase(v.begin() + j);
            }
            else {
                j++;
            }
        }
    }
}
void ensureIntervalOrder(int& l, int& r) {
    if (l > r) {
        std::swap(l, r);
    }
}
void addIntervalSum(std::vector<int>& v, int l, int r) {
    if (l < 0 || r >= (int)v.size() || l > r) {
        throw "Invalid interval.";
    }
    int sum = 0;
    for (int i = l; i <= r; ++i) {
        sum += v[i];
    }
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] += sum;
    }
}
int main() {
    try {
        std::vector<int> staff = inputVector();
        checkEmpty(staff);
        printVector(staff, "Your vector");
        std::cout << "Number of elements: " << staff.size() << "\n";
        long long sum = sumVector(staff);
        std::cout << "Sum of elements: " << sum << "\n";
        replaceZerosWithAverage(staff);
        printVector(staff, "After replacing zeros with average");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int p = safeInput("Enter a number to count elements greater than it: ");
        std::cout << "More than " << p << ": " << countGreaterThan(staff, p) << "\n";
        int m = safeInput("Enter a number to count elements equal to it: ");
        std::cout << "Equal to " << m << ": " << countEqualTo(staff, m) << "\n";
        replaceEvenAbsWithDiff(staff);
        printVector(staff, "After replace by difference");
        eraseDuplicatesByAbs(staff);
        printVector(staff, "After erase duplicates by abs");
        int l = safeInput("Enter left bound of interval: "); 
        int r = safeInput("Enter right bound of interval: ");
        ensureIntervalOrder(l, r);
        addIntervalSum(staff, 1, 3);
        printVector(staff);
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}
