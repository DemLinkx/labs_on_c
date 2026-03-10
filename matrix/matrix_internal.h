#ifndef MATRIX_INTERNAL_H
#define MATRIX_INTERNAL_H

#include <stddef.h>

// Internal structure definition - only visible within the library implementation
struct matrix {
    double* data;  // Storage for matrix elements
    size_t w;      // Width (number of columns)
    size_t h;      // Height (number of rows)
};

#endif
