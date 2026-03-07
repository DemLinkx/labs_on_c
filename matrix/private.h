#ifndef PRIVATE_H
#define PRIVATE_H

#include <stddef.h>

struct matrix {
    double* data;  // Память хранящихся элементов матрицы
    size_t w;      // Ширина (количество столбцов)
    size_t h;      // Высота (количество строк)
};

#endif
