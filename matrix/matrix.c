#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct matrix {
    double* data;
    size_t w;
    size_t h;
};
typedef struct matrix matrix;


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

void m_del(matrix* m)
{
    if (m) {
        free(m->data);
        free(m);
    }
}


double* m_at(matrix* m, size_t i, size_t j)
{
    if (!m || i >= m->h || j >= m->w) {
        return NULL;
    }

    return &m->data[m->w * i + j];
}


const double* m_cat(const matrix* m, size_t i, size_t j)
{
    if (!m || i >= m->h || j >= m->w) {
        return NULL;
    }

    return &m->data[m->w * i + j];
}


int m_set(matrix* m, size_t i, size_t j, double value)
{
    if (!m || i >= m->h || j >= m->w) {
        return -1;
    }

    m->data[m->w * i + j] = value;
    return 0;
}


int m_get(const matrix* m, size_t i, size_t j, double* value)
{
    if (!m || !value || i >= m->h || j >= m->w) {
        return -1;
    }

    *value = m->data[m->w * i + j];
    return 0;
}

size_t m_width(const matrix* m)
{
    return m ? m->w : 0;
}

size_t m_height(const matrix* m)
{
    return m ? m->h : 0;
}

void m_zero(matrix* m)
{
    if (!m) {
        return;
    }

    memset(m->data, 0, m->w * m->h * sizeof(double));
}


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


matrix* m_znew(size_t w, size_t h)
{
    matrix* m = m_new(w, h);
    if (m) {
        m_zero(m);
    }
    return m;
}


matrix* m_enew(size_t w)
{
    matrix* m = m_new(w, w);
    if (m) {
        m_eye(m);
    }
    return m;
}


matrix* m_copy_data(matrix* m1, const matrix* m2)
{
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h) {
        return NULL;
    }

    memcpy(m1->data, m2->data, m1->w * m1->h * sizeof(double));

    return m1;
}

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


double* m_get_data(matrix* m)
{
    return m ? m->data : NULL;
}

const double* m_get_data_const(const matrix* m)
{
    return m ? m->data : NULL;
}

int m_set_dimensions(matrix* m, size_t w, size_t h)
{
    if (!m) return -1;
    m->w = w;
    m->h = h;
    return 0;
}

int m_realloc_data(matrix* m, size_t w, size_t h)
{
    if (!m) return -1;
    double* new_data = (double*)malloc(w * h * sizeof(double));
    if (!new_data) return -1;
    free(m->data);
    m->data = new_data;
    m->w = w;
    m->h = h;
    return 0;
}
