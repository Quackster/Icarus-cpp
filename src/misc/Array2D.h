/*
Written by user2880576
Source: http://stackoverflow.com/questions/365782/how-do-i-best-handle-dynamic-multi-dimensional-arrays-in-c-c
*/

#include <memory>


template <typename T>
class Array2D {

private:
    std::unique_ptr<T> managed_array_;
    T* array_;
    size_t x_, y_;

public:
    Array2D(size_t x, size_t y) {
        managed_array_.reset(new T[x * y]);
        array_ = managed_array_.get();
        y_ = y;
    }
    T* operator[](size_t x) const {
        return &array_[x * y_];
    }
};