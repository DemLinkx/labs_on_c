#include "filter.hpp"
#include "point.hpp" 

template <typename T, typename P>
void remove_if(T* arr, size_t& n, P pred) {
    T* i = arr;
    while (i < arr + n) {
        if (pred(*i)) {
            T* j = i;
            while (j < arr + n - 1) {
                *j = *(j + 1);
                j++;
            }
            n--;
        } else {
            i++;
        }
    }
}

template void remove_if<int, bool(*)(int)>(int* arr, size_t& n, bool(*pred)(int));
template void remove_if<point, bool(*)(point)>(point* arr, size_t& n, bool(*pred)(point));
