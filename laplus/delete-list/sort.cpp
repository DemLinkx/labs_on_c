#include "sort.hpp"
#include "point.hpp"

template <typename T>
void sort(T* arr, size_t n) {
    if (n <= 1) return;
    T* now = arr;
    while (now < arr + n - 1) {
        if (*(now + 1) < *now) {
            T temp = *now;
            *now = *(now + 1);
            *(now + 1) = temp;
            now = arr;
        } else {
            now++;
        }
    }
}

template void sort<int>(int* arr, size_t n);
template void sort<double>(double* arr, size_t n);
template void sort<point>(point* arr, size_t n);