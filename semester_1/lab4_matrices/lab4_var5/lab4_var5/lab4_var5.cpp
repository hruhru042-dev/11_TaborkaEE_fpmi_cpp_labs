
#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>
void clearInput() {
    std::cin.clear();
    while (std::cin.get() != '\n');
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
int getValidInt() {
    int value;
    std::cin >> value;
    if (!std::cin) {
        std::cout << "Error: invalid integer input!\n";
        clearInput();
        exit(1);
    }
    return value;
}
int getChoice() {
    int value;
    std::cin >> value;
    if (!std::cin || (value != 0 && value != 1)) {
        std::cout << "Error: enter 0 or 1!\n";
        clearInput();
        exit(1);
    }
    clearInput();
    return value;
}
void fillArrayRandom(int**& matrix, int n) {
    std::cout << "Enter minimum range limit: ";
    int min_val = getValidInt();
    std::cout << "Enter maximum range limit: ";
    int max_val = getValidInt();
    if (max_val < min_val) {
        std::swap(min_val, max_val);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
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
            matrix[i][j] = getValidInt();
       }
    }
    MatrixOutput(matrix, n);
}
int searchMaxElementLowerRightTriangle(int**& matrix, int n) {
    int max_value;
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
    if (!found) {
        return -1;
    }
    return max_value;
}
int movingMaximumElementToCorner(int**& matrix, int n) {
    int maxVal;
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
        std::cout << "No positive elements!" << std::endl;
        return -1;
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
    std::cout << "Matrix after moving the maximum positive element to [0][0] " << std::endl;
    MatrixOutput(matrix, n);
    return 0;
}
int main() {
    std::cout << "Enter size of square matrix (n x n): ";
    int n = getValidInt();
    if (n <= 0) {
        std::cout << "Matrix size must be positive!" << std::endl;
        return 1;
    }
    int** matrix = nullptr;
    std::cout << "Fill matrix randomly (1) or manually (0)? ";
    AllocateMatrix(matrix, n);
    int choice = getChoice();
    switch (choice) {
    case 1:
        fillArrayRandom(matrix, n);
        break;
    case 0:
        fillArrayManual(matrix, n);
        break;
    }
    int maxInTriangle = searchMaxElementLowerRightTriangle(matrix, n);
    if (maxInTriangle != -1) {
        std::cout << "Maximum element of the lower right triangle of the matrix: " << maxInTriangle << std::endl;
    }
    else {
        std::cout << "No elements in lower right triangle!" << std::endl;
    }
    movingMaximumElementToCorner(matrix, n);
    DeallocateMatrix(matrix, n);
    return 0;
}

