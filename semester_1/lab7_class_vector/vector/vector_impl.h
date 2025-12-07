#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <ostream>
class Vector {
private: 
    size_t size_ = 0;
    size_t capacity_ = 0;
    int* data_ = nullptr;
public:
    Vector();
    Vector(size_t n);
    Vector(std::initializer_list<int> init);
    Vector& operator=(const Vector& other);
    Vector(const Vector& other);
   ~Vector();
    size_t Size() const;
    size_t Capacity() const;
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    int& At(size_t index);
    const int& At(size_t index) const;
    void PushBack(int value);
    void PopBack();
    void Clear();
    void Reserve(size_t new_capacity);
    void Swap(Vector& other);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};


