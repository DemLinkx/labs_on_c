#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstddef>

template <typename T>
void print_array(const char* name, const T* arr, size_t n) {
    std::cout << name << " [" << n << "]: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    std::cout << "\n";
}

#endif