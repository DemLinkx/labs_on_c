#include "bin_s.h"
#include <stddef.h>

int bin_search(void *array, size_t size, size_t count, const void *el, cmp_t cmp) {
    if (array == NULL || el == NULL || cmp == NULL || count == 0) {
        return 0;
    }

    size_t left = 0;
    size_t right = count - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        void *mid_elem = (char *)array + mid * size;
        
        int cmp_result = cmp(el, mid_elem);
        
        if (cmp_result == 0) {
            return 1; 
        } else if (cmp_result < 0) {
            if (mid == 0) break; 
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return 0;
}