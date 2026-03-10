#include "matrix.h"
#include "matrix_internal.h"
#include "ops.h"
#include <string.h>
#include <stdlib.h>


// Adds matrix m2 to m1 in-place: m1 = m1 + m2
// Matrices must have the same dimensions
// Returns 0 on success, -1 on error
int m_add(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h) {
        return -1;
    }

    size_t total = m1->w * m1->h;
    for (size_t i = 0; i < total; i++) {
        m1->data[i] += m2->data[i]; 
    }

    return 0;
}

// Subtracts matrix m2 from m1 in-place: m1 = m1 - m2
// Matrices must have the same dimensions
// Returns 0 on success, -1 on error
int m_sub(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h) {
        return -1;
    }

    size_t total = m1->w * m1->h;
    for (size_t i = 0; i < total; i++) {
        m1->data[i] -= m2->data[i];
    }

    return 0;
}

// Multiplies all matrix elements by scalar d in-place: m = m * d
void m_scale(matrix* m, double d)
{
    if (!m) {
        return;
    }

    size_t total = m->w * m->h;
    for (size_t i = 0; i < total; i++) {
        m->data[i] *= d;
    }
}

// Divides all matrix elements by scalar d in-place: m = m / d
// Does nothing if d == 0.0 (division by zero protection)
void m_sdiv(matrix* m, double d)
{
    if (!m || d == 0.0) {
        return;
    }

    m_scale(m, 1.0 / d);
}

// Adds two matrices into result matrix: m = m1 + m2
// All three matrices must have the same dimensions
// Returns 0 on success, -1 on error
int m_add3(matrix* m, const matrix* m1, const matrix* m2)
{
    if (!m || !m1 || !m2) {
        return -1;
    }

    if (m1->w != m2->w || m1->h != m2->h ||
        m->w != m1->w || m->h != m1->h) {
        return -1;
    }

    size_t total = m->w * m->h;
    for (size_t i = 0; i < total; i++) {
        m->data[i] = m1->data[i] + m2->data[i];
    }

    return 0;
}

// Subtracts two matrices into result matrix: m = m1 - m2
// All three matrices must have the same dimensions
// Returns 0 on success, -1 on error
int m_sub3(matrix* m, const matrix* m1, const matrix* m2)
{
    if (!m || !m1 || !m2) {
        return -1;
    }

    if (m1->w != m2->w || m1->h != m2->h ||
        m->w != m1->w || m->h != m1->h) {
        return -1;
    }

    size_t total = m->w * m->h;
    for (size_t i = 0; i < total; i++) {
        m->data[i] = m1->data[i] - m2->data[i];
    }

    return 0;
}

// Scales matrix m1 by scalar d into result matrix: m = m1 * d
// m and m1 must have the same dimensions
// Returns 0 on success, -1 on error
int m_scale2(matrix* m, const matrix* m1, double d)
{
    if (!m || !m1 || m->w != m1->w || m->h != m1->h) {
        return -1;
    }

    size_t total = m->w * m->h;
    for (size_t i = 0; i < total; i++) {
        m->data[i] = m1->data[i] * d;
    }

    return 0;
}

// Divides matrix m1 by scalar d into result matrix: m = m1 / d
// Returns 0 on success, -1 on error (including division by zero)
int m_sdiv2(matrix* m, const matrix* m1, double d)
{
    if (d == 0.0) {
        return -1;
    }

    return m_scale2(m, m1, 1.0 / d);
}

// Multiplies matrix m1 by matrix m2 and stores result in m1 (in-place)
// m1's width must equal m2's height
// Returns 0 on success, -1 on error
int m_mul(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m1->w != m2->h) {
        return -1;
    }

    matrix* temp = m_new(m2->w, m1->h);
    if (!temp) {
        return -1;
    }

    for (size_t i = 0; i < temp->h; i++) {
        for (size_t j = 0; j < temp->w; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < m1->w; k++) {
                sum += m1->data[m1->w * i + k] * m2->data[m2->w * k + j];
            }
            temp->data[temp->w * i + j] = sum;
        }
    }

    memcpy(m1->data, temp->data, temp->w * temp->h * sizeof(double));
    m1->w = temp->w;
    m1->h = temp->h;

    m_del(temp);
    return 0;
}

// Multiplies matrices m1 and m2, stores result in m: m = m1 * m2
// m1's width must equal m2's height, result matrix m must have correct dimensions
// Returns 0 on success, -1 on error
int m_mul3(matrix* m, const matrix* m1, const matrix* m2)
{
    if (!m || !m1 || !m2 || m1->w != m2->h) {
        return -1;
    }

    size_t new_w = m2->w;
    size_t new_h = m1->h;

    if (m == m1 || m == m2) {
        matrix* temp = m_new(new_w, new_h);
        if (!temp) {
            return -1;
        }

        int result = m_mul3(temp, m1, m2);
        if (result == 0) {
            free(m->data);
            m->data = temp->data;
            m->w = temp->w;
            m->h = temp->h;
            free(temp); 
        }
        else {
            m_del(temp);
        }

        return result;
    }

    if (m->w != new_w || m->h != new_h) {
        return -1;
    }

    for (size_t i = 0; i < new_h; i++) {
        for (size_t j = 0; j < new_w; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < m1->w; k++) {
                sum += m1->data[m1->w * i + k] * m2->data[m2->w * k + j];
            }
            m->data[new_w * i + j] = sum;
        }
    }

    return 0;
}