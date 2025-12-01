#pragma once
#include <cstddef>
#include <initializer_list>
class Vector {

private: 
    size_t size_ = 0;
    size_t capacity_ = 0;
    int* data_ = nullptr;
public:
    Vector();
    Vector(size_t n);
    Vector(std::initializer_list<int>);
    Vector& operator=(const Vector& other);
    Vector(const Vector& other);
   ~Vector();
    void Swap(Vector& other);
    int& operator[](size_t index);
    const int& operator[](size_t index) const;



};

