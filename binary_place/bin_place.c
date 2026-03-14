#include <stdio.h>
#include "b_place.h"


size_t bin_place(const int *array, size_t n, int el) {
    size_t left = 0;
    size_t right = n;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        int val = *(array + mid);
        if (val <= el) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}