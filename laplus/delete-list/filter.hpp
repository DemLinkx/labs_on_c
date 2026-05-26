#ifndef FILTER_H
#define FILTER_H

#include <cstddef>

template <typename T, typename P>
void remove_if(T* arr, size_t& n, P pred);

#endif
