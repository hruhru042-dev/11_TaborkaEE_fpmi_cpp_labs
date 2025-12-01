#include <vector.h>

    Vector::Vector() {};
    Vector::~Vector() {
        delete[] data_;
    }

// your code goes here