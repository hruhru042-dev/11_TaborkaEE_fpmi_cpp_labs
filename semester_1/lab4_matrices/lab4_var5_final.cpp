
#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>
void checkLetter() {
    if (!(std::cin)) {
        throw "Error, this is not a number";
    }
}
void checkNegative(int num) {
    if (num <= 0) {
        throw "Error, number must be positive\n";
    }
}
int getLimit() {
    int limit;
    std::cin >> limit;
    checkLetter();
    return limit;
}
void AllocateMatrix(int**& matrix, int n) {
    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
}
void MatrixOutput(int**& matrix, int n) {
    std::cout << "Your matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(6) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}
void DeallocateMatrix(int**& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
void swapMaxAndMinVal(int& min_val, int& max_val) {
    if (max_val < min_val) {
        std::swap(min_val, max_val);
    }
}
void fillArrayRandom(int**& matrix, int n, std::mt19937& gen) {
    std::cout << "Enter minimum range limit: ";
    int min_val = getLimit();
    std::cout << "Enter maximum range limit: ";
    int max_val = getLimit();
    swapMaxAndMinVal(min_val, max_val);
    std::uniform_int_distribution<int> dist(min_val, max_val);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
    MatrixOutput(matrix, n);
}
void fillArrayManual(int**& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "Element [" << i + 1 << "," << j + 1 << "]: ";
            std::cin >> matrix[i][j];
            checkLetter();
        }
    }
    MatrixOutput(matrix, n);
}
void fillArray(int**& matrix, int size, std::mt19937& gen) {
    int choice;
    std::cout << "How do you want to enter the array: randomly (1) or manually (0)? ";
    std::cin >> choice;
    checkLetter();
    switch (choice) {
    case 1:
        fillArrayRandom(matrix, size, gen);
        break;
    case 0:
        fillArrayManual(matrix, size);
        break;
    default:
        throw "Error, enter 0 or 1\n";
    }
}
int searchMaxElementLowerRightTriangle(int**& matrix, int n) {
    int max_value = 0;
    bool found = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i + j >= n - 1) {
                if (!found || matrix[i][j] > max_value) {
                    max_value = matrix[i][j];
                    found = true;
                }
            }
        }
    }
    return found ? max_value : -1;
}
int movingMaximumElementToCorner(int**& matrix, int n) {
    int maxVal = 0;
    int maxRow = -1;
    int maxCol = -1;
    bool found = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > 0) {
                if (!found || matrix[i][j] > maxVal) {
                    maxVal = matrix[i][j];
                    maxRow = i;
                    maxCol = j;
                    found = true;
                }
            }
        }
    }
    if (!found) {
        throw  "No positive elements!";
    }
    if (maxRow != 0) {
        for (int j = 0; j < n; ++j) {
            std::swap(matrix[0][j], matrix[maxRow][j]);
        }
    }
    if (maxCol != 0) {
        for (int i = 0; i < n; ++i) {
            std::swap(matrix[i][0], matrix[i][maxCol]);
        }
    }
    std::cout << "Maximum positive element in whole matrix: " << maxVal << std::endl;
    std::cout << "Matrix after moving the maximum positive element to [0][0]:\n";
    MatrixOutput(matrix, n);
    return 0;
}
int main() {
    try {
        int n;
        std::cout << "Enter size of square matrix (n x n): ";
        std::cin >> n;
        checkLetter();
        checkNegative(n);
        int** matrix = nullptr;
        AllocateMatrix(matrix, n);
        std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
        fillArray(matrix, n, gen);
        int maxInTriangle = searchMaxElementLowerRightTriangle(matrix, n);
        std::cout << "Maximum element in lower right triangle: " << maxInTriangle << std::endl;
        try {
            movingMaximumElementToCorner(matrix, n);
        }
        catch (const char* msg) {
            std::cout << msg;
            DeallocateMatrix(matrix, n);
            return 1;
        }
        DeallocateMatrix(matrix, n);
    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
    return 0;
}

