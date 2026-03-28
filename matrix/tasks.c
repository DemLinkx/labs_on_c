#include "matrix.h"
#include "tasks.h"
#include "ops.h"
#include "manip.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

static matrix* mat_pow_div_fact(const matrix* a, size_t n, double* fact)
{
    if (n == 0) {
        return m_enew(m_width(a));
    }
    matrix* result = m_dup(a);
    if (!result) return NULL;
    
    for (size_t k = 1; k < n; k++) {
        matrix* temp = m_dup(result);
        if (!temp) {
            m_del(result);
            return NULL;
        }
        if (m_mul3(result, temp, a) != 0) {
            m_del(temp);
            m_del(result);
            return NULL;
        }
        m_del(temp);
    }
    m_sdiv(result, *fact);
    return result;
}

matrix* m_exp(const matrix* a, double eps)
{
    if (!a || m_width(a) != m_height(a)) return NULL;
    
    matrix* result = m_enew(m_width(a));
    if (!result) return NULL;
    
    matrix* term = m_dup(a);
    if (!term) {
        m_del(result);
        return NULL;
    }
    if (m_add(result, term) != 0) {
        m_del(term);
        m_del(result);
        return NULL;
    }
    
    double fact = 1.0;
    size_t n = 2;
    while (m_norm(term) >= eps) {
        fact *= n;
        m_del(term);
        term = mat_pow_div_fact(a, n, &fact);
        if (!term) {
            m_del(result);
            return NULL;
        }
        if (m_add(result, term) != 0) {
            m_del(term);
            m_del(result);
            return NULL;
        }
        n++;
    }
    m_del(term);
    return result;
}

static size_t find_pivot_row(const matrix* a, size_t col)
{
    size_t pivot_row = col;
    size_t w = m_width(a);
    size_t h = m_height(a);
    const double* data = m_get_data_const(a);
    double max_val = fabs(data[w * col + col]);
    
    for (size_t i = col + 1; i < h; i++) {
        double val = fabs(data[w * i + col]);
        if (val > max_val) {
            max_val = val;
            pivot_row = i;
        }
    }
    return pivot_row;
}

int m_solve(const matrix* a, const matrix* b, matrix* x)
{
    if (!a || !b || !x || m_width(a) != m_height(a) || 
        m_height(a) != m_height(b) || m_width(x) != m_width(b) || 
        m_height(x) != m_height(a)) {
        return -1;
    }
    
    size_t n = m_height(a);
    matrix* A = m_dup(a);
    matrix* B = m_dup(b);
    if (!A || !B) {
        m_del(A);
        m_del(B);
        return -1;
    }
    
    for (size_t col = 0; col < n; col++) {
        size_t pivot_row = find_pivot_row(A, col);
        double* a_data = m_get_data(A);
        size_t a_w = m_width(A);
        
        if (fabs(a_data[a_w * pivot_row + col]) < 1e-12) {
            m_del(A);
            m_del(B);
            return -1;
        }
        if (pivot_row != col) {
            m_srow(A, col, pivot_row);
            m_srow(B, col, pivot_row);
        }
        double pivot = a_data[a_w * col + col];
        m_rdiv(A, col, pivot);
        m_rdiv(B, col, pivot);
        
        for (size_t row = 0; row < n; row++) {
            if (row != col) {
                double factor = a_data[a_w * row + col];
                m_radd(A, row, col, -factor);
                m_radd(B, row, col, -factor);
            }
        }
    }
    m_copy_data(x, B);
    m_del(A);
    m_del(B);
    return 0;
}