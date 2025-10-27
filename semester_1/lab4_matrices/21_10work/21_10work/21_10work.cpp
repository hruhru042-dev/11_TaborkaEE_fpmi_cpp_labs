#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
void AllocateMatrix(int**& matrix, int rows, int columns) {
    matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
    }
}
void MatrixOutput(int**& matrix, int rows, int columns) {
    std::cout << "Your matrix:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
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
bool AskComp(int a, int b) { return a < b; }
bool DeskComp(int a, int b) { return a > b; }
void merge(int* a, int left, int mid, int right, int* temp, bool (*comp)(int, int)) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (comp(a[i], a[j])) {
            temp[k++] = a[i++];
        }
        else {
            temp[k++] = a[j++];
        }
    }
    while (i < mid) temp[k++] = a[i++];
    while (j < right) temp[k++] = a[j++];
    for (int t = left; t < right; ++t) {
        a[t] = temp[t];
    }
}
void mergeSort(int* a, int left, int right, int* temp, bool (*comp)(int, int)) {
    if (right - left <= 1) return;
    int mid = (left + right) / 2;
    mergeSort(a, left, mid, temp, comp);
    mergeSort(a, mid, right, temp, comp);
    merge(a, left, mid, right, temp, comp);
}
void SortMatrixRows(int**& matrix, int rows, int columns, bool (*comp)(int, int)) {
    int* temp = new int[columns];
    for (int i = 0; i < rows; ++i) {
        mergeSort(matrix[i], 0, columns, temp, comp);
    }
    delete[] temp;
}
void BubbleSortRows(int**& matrix, int rows, int columns, bool (*comp)(int, int)) {
    for (int r = 0; r < rows; ++r) {
        for (int i = 0; i < columns - 1; ++i) {
            for (int j = 0; j < columns - i - 1; ++j) {
                if (!comp(matrix[r][j], matrix[r][j + 1])) {
                    std::swap(matrix[r][j], matrix[r][j + 1]);
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
            while (j >= 0 && !comp(matrix[r][j], tmp)) {
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
        std::fill(count, count + MAX_VALUE, 0);
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
        if (comp(0, 1)) {
            for (int val = 0; val < MAX_VALUE; ++val) {
                while (count[val]-- > 0) matrix[r][index++] = val;
            }
        }
        else {
            for (int val = MAX_VALUE - 1; val >= 0; --val) {
                while (count[val]-- > 0) matrix[r][index++] = val;
            }
        }
    }
}
int main() {
    int n, m;
    std::cout << "Enter number of rows: ";
    std::cin >> n;
    CheckEnter();
    std::cout << "Enter number of columns: ";
    std::cin >> m;
    CheckEnter();
    int** matrix = nullptr;
    int choice;
    std::cout << "How do you want to enter the array: randomly (1) or manually (0)? ";
    std::cin >> choice;
    CheckEnter();
    AllocateMatrix(matrix, n, m);
    if (choice == 1) {
        int min_val, max_val;
        std::cout << "Enter minimum range limit: ";
        std::cin >> min_val;
        CheckEnter();
        std::cout << "Enter maximum range limit: ";
        std::cin >> max_val;
        CheckEnter();
        if (max_val < min_val) std::swap(min_val, max_val);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min_val, max_val);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                matrix[i][j] = dist(gen);
    }
    else if (choice == 0) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                std::cout << "Element [" << i << "][" << j << "]: ";
                std::cin >> matrix[i][j];
                CheckEnter();
            }
    }
    else {
        std::cout << "Invalid input. Exiting.\n";
        Deallocate(matrix, n);
        return 1;
    }
    MatrixOutput(matrix, n, m);
    int sortMethod;
    std::cout << "Choose sorting method:\n"
        << "1 - Bubble Sort\n"
        << "2 - Insertion Sort\n"
        << "3 - Counting Sort\n"
        << "4 - Merge Sort\n";
    std::cin >> sortMethod;
    CheckEnter();
    int order;
    std::cout << "Choose sorting order: 0 - ascending, 1 - descending: ";
    std::cin >> order;
    CheckEnter();
    bool (*comp)(int, int) = (order == 0) ? AskComp : DeskComp;
    switch (sortMethod) {
    case 1: BubbleSortRows(matrix, n, m, comp); break;
    case 2: InsertionSortRows(matrix, n, m, comp); break;
    case 3: CountingSortRows(matrix, n, m, comp); break;
    case 4: SortMatrixRows(matrix, n, m, comp); break;
    default:
        std::cout << "Invalid sorting method.\n";
        Deallocate(matrix, n);
        return 1;
    }
    std::cout << "\nSorted matrix:\n";
    MatrixOutput(matrix, n, m);
    Deallocate(matrix, n);
    return 0;
}

