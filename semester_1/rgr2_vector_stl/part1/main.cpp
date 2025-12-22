#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <limits> 
#include <unordered_set>
#include <iterator>
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
    if (!std::cin) { 
        throw "Invalid input: expected integer.";
    }
    return v;
}
int safeInput() {
    int value;
    if (!(std::cin >> value)) {
        throw "Invalid input: expected integer.";
    }
    return value;
}
void printVector(const std::vector<int>& v, const std::string& msg = "Vector") {
    std::cout << msg << ": ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}
void replaceZerosWithAverage(std::vector<int>& v) {
    long long sum = std::accumulate(v.begin(), v.end(), 0LL);
    int avg = sum / static_cast<int>(v.size());
    std::replace_if(v.begin(), v.end(),
        [](int n) { return n == 0; },
        avg);
}
void replaceEvenAbsWithDiff(std::vector<int>& v) {
    if (v.empty()) return;
    auto [minIt, maxIt] = std::minmax_element(v.begin(), v.end());
    int diff = *maxIt - *minIt;
    std::replace_if(v.begin(), v.end(),
        [](int n) { return std::abs(n) % 2 == 0; },
        diff);
}
void eraseDuplicatesByAbs(std::vector<int>& v) {
    std::unordered_set<int> seen;
    v.erase(std::remove_if(v.begin(), v.end(),
        [&](int n) {
            int absVal = std::abs(n);
            if (seen.find(absVal) != seen.end()) {
                return true; // удалить
            }
            seen.insert(absVal);
            return false; // оставить
        }),
        v.end());
}
void ensureIntervalOrder(int& l, int& r) {
    auto [lo, hi] = std::minmax(l, r);
    l = lo; r = hi;
}

void addIntervalSum(std::vector<int>& v, int l, int r) {
    if (l < 0 || r >= static_cast<int>(v.size()) || l > r) {
        throw "Invalid interval.";
    }
    int sum = std::accumulate(v.begin() + l, v.begin() + r + 1, 0);
    std::for_each(v.begin(), v.end(), [&](int& n) {
        n += sum;
        });
}
int main() {
    try {
        std::vector<int> staff = inputVector();
        checkEmpty(staff);
        printVector(staff, "Your vector");
        std::cout << "Number of elements: " << staff.size() << "\n";
        long long sum = std::accumulate(staff.begin(), staff.end(), 0LL);
        std::cout << "Sum of elements: " << sum << "\n";
        replaceZerosWithAverage(staff);
        printVector(staff, "After replacing zeros with average");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number to count elements greater than it: " << "\n";
        int p = safeInput();
        std::cout << "More than " << p << ": " << std::count_if(staff.begin(), staff.end(), [&](int n) { return n > p; }) << "\n";
        std::cout << "Enter a number to count elements equal to it: " << "\n";
        int m = safeInput();
        std::cout << "Equal to " << m << ": " << std::count(staff.begin(), staff.end(), m) << "\n";
        replaceEvenAbsWithDiff(staff);
        printVector(staff, "After replace by difference");
        eraseDuplicatesByAbs(staff);
        printVector(staff, "After erase duplicates by abs");
        std::cout << "Enter left bound of interval: " << "\n";
        int l = safeInput(); 
        std::cout << "Enter right bound of interval: " << "\n";
        int r = safeInput();
        ensureIntervalOrder(l, r);
        addIntervalSum(staff, l, r);
        printVector(staff);
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}
