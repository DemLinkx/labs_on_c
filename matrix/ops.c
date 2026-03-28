#include "matrix.h"
#include "ops.h"
#include <string.h>
#include <stdlib.h>

int m_add(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m_width(m1) != m_width(m2) || m_height(m1) != m_height(m2)) {
        return -1;
    }
    size_t total = m_width(m1) * m_height(m1);
    double* d1 = m_get_data(m1);
    const double* d2 = m_get_data_const(m2);
    for (size_t i = 0; i < total; i++) {
        d1[i] += d2[i];
    }
    return 0;
}

int m_sub(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m_width(m1) != m_width(m2) || m_height(m1) != m_height(m2)) {
        return -1;
    }
    size_t total = m_width(m1) * m_height(m1);
    double* d1 = m_get_data(m1);
    const double* d2 = m_get_data_const(m2);
    for (size_t i = 0; i < total; i++) {
        d1[i] -= d2[i];
    }
    return 0;
}

void m_scale(matrix* m, double d)
{
    if (!m) return;
    size_t total = m_width(m) * m_height(m);
    double* data = m_get_data(m);
    for (size_t i = 0; i < total; i++) {
        data[i] *= d;
    }
}

void m_sdiv(matrix* m, double d)
{
    if (!m || d == 0.0) return;
    m_scale(m, 1.0 / d);
}

int m_add3(matrix* m, const matrix* m1, const matrix* m2)
{
    if (!m || !m1 || !m2) return -1;
    if (m_width(m1) != m_width(m2) || m_height(m1) != m_height(m2) ||
        m_width(m) != m_width(m1) || m_height(m) != m_height(m1)) {
        return -1;
    }
    size_t total = m_width(m) * m_height(m);
    double* d = m_get_data(m);
    const double* d1 = m_get_data_const(m1);
    const double* d2 = m_get_data_const(m2);
    for (size_t i = 0; i < total; i++) {
        d[i] = d1[i] + d2[i];
    }
    return 0;
}

int m_sub3(matrix* m, const matrix* m1, const matrix* m2)
{
    if (!m || !m1 || !m2) return -1;
    if (m_width(m1) != m_width(m2) || m_height(m1) != m_height(m2) ||
        m_width(m) != m_width(m1) || m_height(m) != m_height(m1)) {
        return -1;
    }
    size_t total = m_width(m) * m_height(m);
    double* d = m_get_data(m);
    const double* d1 = m_get_data_const(m1);
    const double* d2 = m_get_data_const(m2);
    for (size_t i = 0; i < total; i++) {
        d[i] = d1[i] - d2[i];
    }
    return 0;
}

int m_scale2(matrix* m, const matrix* m1, double d)
{
    if (!m || !m1 || m_width(m) != m_width(m1) || m_height(m) != m_height(m1)) {
        return -1;
    }
    size_t total = m_width(m) * m_height(m);
    double* d_out = m_get_data(m);
    const double* d_in = m_get_data_const(m1);
    for (size_t i = 0; i < total; i++) {
        d_out[i] = d_in[i] * d;
    }
    return 0;
}

int m_sdiv2(matrix* m, const matrix* m1, double d)
{
    if (d == 0.0) return -1;
    return m_scale2(m, m1, 1.0 / d);
}

int m_mul(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m_width(m1) != m_height(m2)) return -1;
    
    size_t new_w = m_width(m2);
    size_t new_h = m_height(m1);
    size_t k_dim = m_width(m1);
    
    matrix* temp = m_new(new_w, new_h);
    if (!temp) return -1;
    
    const double* d1 = m_get_data_const(m1);
    const double* d2 = m_get_data_const(m2);
    double* d_temp = m_get_data(temp);
    
    for (size_t i = 0; i < new_h; i++) {
        for (size_t j = 0; j < new_w; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < k_dim; k++) {
                sum += d1[k_dim * i + k] * d2[new_w * k + j];
            }
            d_temp[new_w * i + j] = sum;
        }
    }
    
    // Копируем результат обратно в m1
    m_copy_data(m1, temp);
    m_set_dimensions(m1, new_w, new_h);
    m_del(temp);
    return 0;
}

int m_mul3(matrix* m, const matrix* m1, const matrix* m2)
{
    if (!m || !m1 || !m2 || m_width(m1) != m_height(m2)) return -1;
    
    size_t new_w = m_width(m2);
    size_t new_h = m_height(m1);
    size_t k_dim = m_width(m1);
    
    if (m == m1 || m == m2) {
        matrix* temp = m_new(new_w, new_h);
        if (!temp) return -1;
        int result = m_mul3(temp, m1, m2);
        if (result == 0) {
            m_copy_data(m, temp);
            m_set_dimensions(m, new_w, new_h);
        }
        m_del(temp);
        return result;
    }
    
    if (m_width(m) != new_w || m_height(m) != new_h) return -1;
    
    const double* d1 = m_get_data_const(m1);
    const double* d2 = m_get_data_const(m2);
    double* d_out = m_get_data(m);
    
    for (size_t i = 0; i < new_h; i++) {
        for (size_t j = 0; j < new_w; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < k_dim; k++) {
                sum += d1[k_dim * i + k] * d2[new_w * k + j];
            }
            d_out[new_w * i + j] = sum;
        }
    }
    return 0;
}