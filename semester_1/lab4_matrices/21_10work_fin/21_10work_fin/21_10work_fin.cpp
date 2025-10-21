
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
void AllocateMatrix(int**& matrix, int rows, int colloms) {
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[colloms];
    }
}
void MatrixOutput(int**& matrix, int rows, int colloms) {
    std::cout << "Your matrix: " << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < colloms; ++j) {
            std::cout << std::setw(5) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}
void Deallocate(int**& matrix, int rows) {
    if (matrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
void CheckEnter() {
    if (!(std::cin)) {
        std::cout << "Enter a number!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}
void merge(int* a, int left, int mid, int right, int* temp) {
    int i = left;
    int j = mid;
    int k = left;
    while (i < mid && j < right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        }
        else {
            temp[k++] = a[j++];
        }
    }
    while (i < mid) {
        temp[k++] = a[i++];
    }
    while (j < right) {
        temp[k++] = a[j++];
    }
    for (int t = left; t < right; ++t) {
        a[t] = temp[t];
    }
}
void mergeSort(int* a, int left, int right, int* temp, bool (*comp)(int, int)) {
    if (right - left <= 1) return;
    int mid = (left + right) / 2;
    mergeSort(a, left, mid, temp);
    mergeSort(a, mid, right, temp);
    merge(a, left, mid, right, temp);
}
void SortMatrixRows(int**& matrix, int rows, int columns, bool (*comp)(int, int)) {
    int* temp = new int[columns]; 
    for (int i = 0; i < rows; ++i) {
        mergeSort(matrix[i], 0, columns, temp); 
    }
    delete[] temp;
}
void BubbleSortRows(int**& matrix, int rows, int columns, bool (*comp)(int, int)) {
    for (int r = 0; r < rows; ++r) {
        for (int i = 0; i < columns - 1; ++i) {
            for (int j = 0; j < columns - i - 1; ++j) {
                if (matrix[r][j] > matrix[r][j + 1]) {
                    int temp = matrix[r][j];
                    matrix[r][j] = matrix[r][j + 1];
                    matrix[r][j + 1] = temp;
                }
            }
        }
    }
}
void InsertionSortRows(int** matrix, int rows, int columns, bool (*comp)(int, int)) {
    for (int r = 0; r < rows; ++r) {
        for (int i = 1; i < columns; ++i) {
            int tmp = matrix[r][i];
            int j = i - 1;
            while (j >= 0 && matrix[r][j] > tmp) {
                matrix[r][j + 1] = matrix[r][j];
                --j;
            }
            matrix[r][j + 1] = tmp;
        }
    }
}
void CountingSortRows(int** matrix, int rows, int columns, bool (*comp)(int, int)) {
    const int MAX_VALUE = 100; 
    int count[MAX_VALUE];
    for (int r = 0; r < rows; ++r) {
        for (int i = 0; i < MAX_VALUE; ++i) {
            count[i] = 0;
        }
        for (int j = 0; j < columns; ++j) {
            int value = matrix[r][j];
            if (value >= 0 && value < MAX_VALUE) {
                ++count[value];
            }
            else {
                std::cout << "Value out of range in matrix[" << r << "][" << j << "]: " << value << std::endl;
            }
        }
        int index = 0;
        for (int val = 0; val < MAX_VALUE; ++val) {
            while (count[val] > 0) {
                matrix[r][index++] = val;
                --count[val];
            }
        }
    }
}
bool AskComp(int a, int b) {
    return a < b;
}
bool DeskComp(int a, int b) {
    return a > b;
}
int main()
{
    int n, m;
    std::cout << "Enter number of lines" << std::endl;
    std::cin >> n;
    CheckEnter();
    std::cout << "Enter number of collons" << std::endl;
    std::cin >> m;
    CheckEnter();
    int** matrix = nullptr;
    int choice;
    std::cout << "How do you want to enter the array: randomly (enter 1) or by yourself (enter 0)? ";
    std::cin >> choice;
    CheckEnter();
    switch (choice) {
    case 1: {
        AllocateMatrix(matrix, n, m);
        srand(static_cast<unsigned>(time(0)));
        int min_val, max_val;
        std::cout << "Enter minimum range limit: ";
        std::cin >> min_val;
        CheckEnter();
        std::cout << "Enter maximum range limit: ";
        std::cin >> max_val;
        CheckEnter();
        if (max_val < min_val) {
            int temp = max_val;
            max_val = min_val;
            min_val = temp;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min_val, max_val);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = dist(gen);
            }
        }
        MatrixOutput(matrix, n, m);
        break;
    }
    case 0: {
        AllocateMatrix(matrix, n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << "Element [" << i << "][" << j << "]" << std::endl;
                std::cin >> matrix[i][j];
                CheckEnter();
            }
        }
        MatrixOutput(matrix, n, m);
        break;
    }
    default:
        std::cout << "Enter 1 or 0. \n";
        Deallocate(matrix, n);
        return 1;
    }
    int meaning;
    std::cout << "How do you want to sort the array? Enter: " << std::endl;
    std::cout << "1 - bubble sort" << std::endl;
    std::cout << "2 - insertion sort" << std::endl;
    std::cout << "3 - counting sort" << std::endl;
    std::cout << "4 - merge sort" << std::endl;
    std::cin >> meaning;
    CheckEnter();
    switch (meaning) {
    case 1: {
        BubbleSortRows(matrix, n, m);
        break;
    }
    case 2: {
        InsertionSortRows(matrix, n, m);
        break;
    }
    case 3: {
        CountingSortRows(matrix, n, m);
        break;
    }
    case 4: {
        SortMatrixRows(matrix, n, m);
        break;
    }
    default:
        std::cout << "Enter 1, 2, 3 or 4" << std::endl;
        Deallocate(matrix, n);
        return 1;
    }
    return 0;
}


