#ifndef TASKS_H
#define TASKS_H

#include "matrix.h"

/**
 * Calculate matrix exponential: exp(A) = E + A + A^2/2! + A^3/3! + ...
 * a - square matrix
 * eps - precision (stops when term norm < eps)
 * returns new matrix with result or NULL on error
 */
matrix* m_exp(const matrix* a, double eps);

/**
 * Solve system of linear equations Ax = b (Gaussian elimination with partial pivoting)
 * a - square matrix (must be non-singular)
 * b - right-hand side matrix
 * x - result matrix (must be pre-allocated)
 * returns 0 on success, -1 on error (singular matrix or dimension mismatch)
 */
int m_solve(const matrix* a, const matrix* b, matrix* x);

#endif 
