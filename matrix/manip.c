#include "matrix.h"
#include "private.h"
#include "manip.h"
#include <stdlib.h>
#include <math.h>

// Transposes matrix in-place: swaps rows and columns
// Works for both square and rectangular matrices
// Returns 0 on success, -1 on error
int m_tr(matrix* m)
{
    if (!m) {
        return -1;
    }

    if (m->w == m->h) {
        for (size_t i = 0; i < m->h; i++) {
            for (size_t j = i + 1; j < m->w; j++) {
                double tmp = m->data[m->w * i + j];
                m->data[m->w * i + j] = m->data[m->w * j + i];
                m->data[m->w * j + i] = tmp;
            }
        }
        return 0;
    }

    double* new_data = (double*)malloc(m->h * m->w * sizeof(double));
    if (!new_data) {
        return -1;
    }

    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++) {
            new_data[m->h * j + i] = m->data[m->w * i + j];
        }
    }

    free(m->data);
    m->data = new_data;

    size_t tmp = m->w;
    m->w = m->h;
    m->h = tmp;

    return 0;
}

// Swaps rows i and j in the matrix
// Returns 0 on success, -1 if indices are out of bounds
int m_srow(matrix* m, size_t i, size_t j)
{
    if (!m || i >= m->h || j >= m->h) {
        return -1;
    }

    if (i == j) {
        return 0;
    }

    for (size_t col = 0; col < m->w; col++) {
        double tmp = m->data[m->w * i + col];
        m->data[m->w * i + col] = m->data[m->w * j + col];
        m->data[m->w * j + col] = tmp;
    }

    return 0;
}

// Swaps columns i and j in the matrix
// Returns 0 on success, -1 if indices are out of bounds
int m_scol(matrix* m, size_t i, size_t j)
{
    if (!m || i >= m->w || j >= m->w) {
        return -1;
    }

    if (i == j) {
        return 0;
    }

    for (size_t row = 0; row < m->h; row++) {
        double tmp = m->data[m->w * row + i];
        m->data[m->w * row + i] = m->data[m->w * row + j];
        m->data[m->w * row + j] = tmp;
    }

    return 0;
}

// Multiplies row i by scalar d in-place: row[i] *= d
// Returns 0 on success, -1 if index is out of bounds
int m_rmul(matrix* m, size_t i, double d)
{
    if (!m || i >= m->h) {
        return -1;
    }

    for (size_t j = 0; j < m->w; j++) {
        m->data[m->w * i + j] *= d;
    }

    return 0;
}

// Divides row i by scalar d in-place: row[i] /= d
// Returns 0 on success, -1 if index is out of bounds or d == 0.0
int m_rdiv(matrix* m, size_t i, double d)
{
    if (!m || i >= m->h || d == 0.0) {
        return -1;
    }

    return m_rmul(m, i, 1.0 / d);
}

// Adds row 'from' multiplied by coefficient to row 'to': row[to] += coeff * row[from]
// Used in Gaussian elimination and matrix decomposition
// Returns 0 on success, -1 if indices are out of bounds
int m_radd(matrix* m, size_t to, size_t from, double coeff)
{
    if (!m || to >= m->h || from >= m->h) {
        return -1;
    }

    for (size_t j = 0; j < m->w; j++) {
        m->data[m->w * to + j] += coeff * m->data[m->w * from + j];
    }

    return 0;
}

// Calculates the infinity norm (maximum absolute row sum) of the matrix
// Returns the norm value, -1.0 if matrix is NULL
double m_norm(const matrix* m)
{
    if (!m) {
        return -1.0;
    }

    double max_row_sum = 0.0;

    for (size_t i = 0; i < m->h; i++) {
        double row_sum = 0.0;
        for (size_t j = 0; j < m->w; j++) {
            row_sum += fabs(m->data[m->w * i + j]);
        }
        if (row_sum > max_row_sum) {
            max_row_sum = row_sum;
        }
    }

    return max_row_sum;
}