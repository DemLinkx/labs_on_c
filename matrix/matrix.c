#include "matrix.h"
#include "private.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creates a new matrix with width w and height h
// Returns a pointer to matrix or NULL on error allocation failure
matrix* m_new(size_t w, size_t h)
{
    if (w == 0 || h == 0) return NULL;

    matrix* m = (matrix*)malloc(sizeof(struct matrix)); 
    if (!m) return NULL;

    m->data = (double*)malloc(w * h * sizeof(double));
    if (!m->data) {
        free(m);
        return NULL;
    }

    m->w = w;
    m->h = h;

    return m;
}

// Duplicates a matrix - creates a deep copy
// Returns a pointer to new matrix or NULL on allocation failure
matrix* m_dup(const matrix* m)
{
    if (!m) {
        return NULL;
    }

    matrix* new_m = m_new(m->w, m->h);
    if (!new_m) {
        return NULL;
    }

    memcpy(new_m->data, m->data, m->w * m->h * sizeof(double));

    return new_m;
}

// Frees matrix memory - deallocates both data and matrix structure
void m_del(matrix* m)
{
    if (m) {
        free(m->data);
        free(m);
    }
}

// Gets a mutable pointer to matrix element at position (i, j)
// Returns pointer or NULL if indices are out of bounds
double* m_at(matrix* m, size_t i, size_t j)
{
    if (!m || i >= m->h || j >= m->w) {
        return NULL;
    }

    return &m->data[m->w * i + j];
}

// Gets a const pointer to matrix element at position (i, j)
// Returns const pointer or NULL if indices are out of bounds
const double* m_cat(const matrix* m, size_t i, size_t j)
{
    if (!m || i >= m->h || j >= m->w) {
        return NULL;
    }

    return &m->data[m->w * i + j];
}

// Sets the value at matrix position (i, j)
// Returns 0 on success, -1 if indices are out of bounds
int m_set(matrix* m, size_t i, size_t j, double value)
{
    if (!m || i >= m->h || j >= m->w) {
        return -1;
    }

    m->data[m->w * i + j] = value;
    return 0;
}

// Gets the value at matrix position (i, j)
// Returns 0 on success, -1 if indices are out of bounds or value is NULL
int m_get(const matrix* m, size_t i, size_t j, double* value)
{
    if (!m || !value || i >= m->h || j >= m->w) {
        return -1;
    }

    *value = m->data[m->w * i + j];
    return 0;
}

// Returns the width of the matrix
size_t m_width(const matrix* m)
{
    return m ? m->w : 0;
}

// Returns the height of the matrix
size_t m_height(const matrix* m)
{
    return m ? m->h : 0;
}

// Fills the matrix with zeros
void m_zero(matrix* m)
{
    if (!m) {
        return;
    }

    memset(m->data, 0, m->w * m->h * sizeof(double));
}

// Converts matrix to identity matrix (1s on diagonal, 0s elsewhere)
// Only works for square matrices - returns NULL if not square
matrix* m_eye(matrix* m)
{
    if (!m || m->w != m->h) {
        return NULL;
    }

    m_zero(m);

    for (size_t i = 0; i < m->h; i++) {
        m->data[m->w * i + i] = 1.0;
    }

    return m;
}

// Creates a new zero matrix with width w and height h
// Returns pointer to matrix or NULL on allocation failure
matrix* m_znew(size_t w, size_t h)
{
    matrix* m = m_new(w, h);
    if (m) {
        m_zero(m);
    }
    return m;
}

// Creates a new identity matrix of size w x w
// Returns pointer to identity matrix or NULL on allocation failure
matrix* m_enew(size_t w)
{
    matrix* m = m_new(w, w);
    if (m) {
        m_eye(m);
    }
    return m;
}

// Copies data from matrix m2 to matrix m1
// Matrices must have the same dimensions
// Returns m1 on success, NULL on error
matrix* m_copy_data(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h) {
        return NULL;
    }

    memcpy(m1->data, m2->data, m1->w * m1->h * sizeof(double));

    return m1;
}

// Prints the matrix to stdout in a formatted way
void m_print(const matrix* m)
{
    if (!m) {
        printf("NULL matrix\n");
        return;
    }

    printf("Matrix [%zu x %zu]:\n", m->w, m->h);
    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++) {
            printf("%8.3f ", m->data[m->w * i + j]);
        }
        printf("\n");
    }
}

// Reads matrix elements from stdin
// Creates w x h matrix and fills with values from input
// Returns pointer to matrix or NULL on allocation failure or input error
matrix* m_read(size_t w, size_t h)
{
    matrix* m = m_new(w, h);
    if (!m) {
        return NULL;
    }

    printf("Enter %zu x %zu matrix:\n", w, h);
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            if (scanf("%lf", &m->data[m->w * i + j]) != 1) {
                m_del(m);
                return NULL;
            }
        }
    }

    return m;
}