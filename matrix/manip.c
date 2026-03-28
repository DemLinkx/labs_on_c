#include "matrix.h"
#include "manip.h"
#include <stdlib.h>
#include <math.h>
#include <string.h> 


int m_tr(matrix* m)
{
    if (!m) return -1;
    
    size_t w = m_width(m);
    size_t h = m_height(m);
    
    if (w == h) {
        double* data = m_get_data(m);
        for (size_t i = 0; i < h; i++) {
            for (size_t j = i + 1; j < w; j++) {
                double tmp = data[w * i + j];
                data[w * i + j] = data[w * j + i];
                data[w * j + i] = tmp;
            }
        }
        return 0;
    }
    
    // Для неквадратных — перевыделяем память
    double* new_data = (double*)malloc(h * w * sizeof(double));
    if (!new_data) return -1;
    
    const double* old_data = m_get_data_const(m);
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            new_data[h * j + i] = old_data[w * i + j];
        }
    }
    
    free(m_get_data(m));
    // Нужно установить новые данные через специальную функцию
    // Добавим это в matrix.h как m_set_data или используем m_realloc_data
    m_realloc_data(m, h, w);
    double* m_data = m_get_data(m);
    memcpy(m_data, new_data, h * w * sizeof(double));
    free(new_data);
    return 0;
}

int m_srow(matrix* m, size_t i, size_t j)
{
    if (!m || i >= m_height(m) || j >= m_height(m)) return -1;
    if (i == j) return 0;
    
    size_t w = m_width(m);
    double* data = m_get_data(m);
    for (size_t col = 0; col < w; col++) {
        double tmp = data[w * i + col];
        data[w * i + col] = data[w * j + col];
        data[w * j + col] = tmp;
    }
    return 0;
}

int m_scol(matrix* m, size_t i, size_t j)
{
    if (!m || i >= m_width(m) || j >= m_width(m)) return -1;
    if (i == j) return 0;
    
    size_t w = m_width(m);
    size_t h = m_height(m);
    double* data = m_get_data(m);
    for (size_t row = 0; row < h; row++) {
        double tmp = data[w * row + i];
        data[w * row + i] = data[w * row + j];
        data[w * row + j] = tmp;
    }
    return 0;
}

int m_rmul(matrix* m, size_t i, double d)
{
    if (!m || i >= m_height(m)) return -1;
    
    size_t w = m_width(m);
    double* data = m_get_data(m);
    for (size_t j = 0; j < w; j++) {
        data[w * i + j] *= d;
    }
    return 0;
}

int m_rdiv(matrix* m, size_t i, double d)
{
    if (!m || i >= m_height(m) || d == 0.0) return -1;
    return m_rmul(m, i, 1.0 / d);
}

int m_radd(matrix* m, size_t to, size_t from, double coeff)
{
    if (!m || to >= m_height(m) || from >= m_height(m)) return -1;
    
    size_t w = m_width(m);
    double* data = m_get_data(m);
    for (size_t j = 0; j < w; j++) {
        data[w * to + j] += coeff * data[w * from + j];
    }
    return 0;
}

double m_norm(const matrix* m)
{
    if (!m) return -1.0;
    
    double max_row_sum = 0.0;
    size_t w = m_width(m);
    size_t h = m_height(m);
    const double* data = m_get_data_const(m);
    
    for (size_t i = 0; i < h; i++) {
        double row_sum = 0.0;
        for (size_t j = 0; j < w; j++) {
            row_sum += fabs(data[w * i + j]);
        }
        if (row_sum > max_row_sum) {
            max_row_sum = row_sum;
        }
    }
    return max_row_sum;
}