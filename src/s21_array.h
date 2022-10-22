#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cmath>
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <class T, size_t N = 0>
class array {
   public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

    array() : size_(N) { data_[N] = {}; }

    array(std::initializer_list<value_type> const &items) : size_(N) {
        size_type i = 0;
        for (auto it = items.begin(); i < size_; ++it, ++i) {
            data_[i] = *it;
        }
    }

    array(const array &a) : size_(a.size_) {
        for (size_type i = 0; i < a.size_; ++i) {
            data_[i] = a.data_[i];
        }
    }

    array(array &&a) = default;

    ~array() = default;

    void operator=(array &&a) {
        if (this != &a) {
            size_type i = 0;
            for (auto it = begin(); it != end(); ++it, ++i) {
                *it = a.data_[i];
            }
        }
    }

    reference at(size_type pos) {
        if (pos >= size_ && size_ == 0) {
            throw std::out_of_range("Index out of range!");
        }
        return data_[pos];
    }

    reference operator[](size_type pos) { return at(pos); }
    const_reference front() { return at(0); }
    const_reference back() { return at(size_ - 1); }
    iterator data() { return data_; }

    iterator begin() { return data_; }
    iterator end() { return &data_[size_]; }

    bool empty() { return size_ == 0; }
    size_type size() { return size_; }
    size_type max_size() { return size_; }

    void swap(array &other) {
        array<T, N> tmp(other);
        other = *this;
        *this = tmp;
    }

    void fill(const_reference value) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

   private:
    value_type data_[N];
    size_type size_;
};

};  // namespace s21

#endif  // SRC_S21_ARRAY_H_