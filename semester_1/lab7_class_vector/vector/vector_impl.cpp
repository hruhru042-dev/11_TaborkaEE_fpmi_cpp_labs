#include "vector_impl.h"
#include <algorithm>
Vector::Vector() {}
Vector::~Vector() {
    delete[] data_;
}
Vector::Vector(size_t value)
    : size_(value),
      capacity_(size_), data_(new int[capacity_] {}) {}
Vector::Vector(std::initializer_list<int> init)
    : size_(init.size()), capacity_(size_), data_(new int[capacity_]) {
    std::copy(init.begin(), init.end(), data_);
}
Vector::Vector(const Vector& other)
    : size_(other.size_),
      capacity_(other.capacity_), data_(new int[capacity_]) {
    std::copy(other.data_, other.data_+other.size_, data_);
}
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        int* newData = new int[other.capacity_];
        std::copy(other.data_,other.data_+other.size_, newData);
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    return *this;
}
void Vector::Swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}
int& Vector::operator[](size_t index) {
    return data_[index];
}
const int& Vector::operator[](size_t index) const {
    return data_[index];
}
int& Vector::At(const size_t index) {
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data_[index];
}
const int& Vector::At(const size_t index) const{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data_[index];
}
size_t Vector::Size() const {
    return size_;
}
size_t Vector::Capacity() const {
    return capacity_;
}
void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}
void Vector::PushBack(int value) {
    if (capacity_ > size_) {
        data_[size_++] = value;
    } else {
        if (capacity_ > 0) {
            capacity_ *= 2;
        } else {
            capacity_ = 1;
        }
        int* newData = new int[capacity_];
        std::copy(data_, data_ + size_, newData);
        newData[size_++] = value;
        delete[] data_;
        data_ = newData;
    }
}
void Vector::Clear() {
    size_ = 0;
}
void Vector::Reserve(const size_t new_capacity) {
    if (new_capacity < capacity_) {
        return;
    } else{  
        int* newData = new int[new_capacity];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = new_capacity;
    }
}
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (size_t i = 0; i < v.size_; ++i) {
        os << v.data_[i];
        if (i + 1 < v.size_)
            os << ", ";
    }
    os << "]";
    return os;
}
      // your code goes here