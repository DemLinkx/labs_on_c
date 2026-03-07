#ifndef OPS_H
#define OPS_H

#include "matrix.h"

/**
 * m1 += m2
 * m1 - left matrix
 * m2 - right matrix
 * returns 0 on success, -1 if dimensions mismatch
 */
int m_add(matrix* m1, const matrix* m2);

/**
 * m1 -= m2
 * m1 - left matrix
 * m2 - right matrix
 * returns 0 on success, -1 if dimensions mismatch
 */
int m_sub(matrix* m1, const matrix* m2);

/**
 * m *= d
 * m - matrix
 * d - scalar
 */
void m_scale(matrix* m, double d);

/**
 * m /= d
 * m - matrix
 * d - scalar
 */
void m_sdiv(matrix* m, double d);

/**
 * m = m1 + m2
 * m - result matrix
 * m1 - first operand
 * m2 - second operand
 * returns 0 on success, -1 on error (dimensions mismatch)
 */
int m_add3(matrix* m, const matrix* m1, const matrix* m2);

/**
 * m = m1 - m2
 * m - result matrix
 * m1 - first operand
 * m2 - second operand
 * returns 0 on success, -1 on error (dimensions mismatch)
 */
int m_sub3(matrix* m, const matrix* m1, const matrix* m2);

/**
 * m = m1 * d
 * m - result matrix
 * m1 - source matrix
 * d - scalar
 * returns 0 on success, -1 on error (dimensions mismatch)
 */
int m_scale2(matrix* m, const matrix* m1, double d);

/**
 * m = m1 / d
 * m - result matrix
 * m1 - source matrix
 * d - scalar
 * returns 0 on success, -1 on error (dimensions mismatch or division by zero)
 */
int m_sdiv2(matrix* m, const matrix* m1, double d);

/**
 * m1 *= m2
 * m1 - left matrix with result stored
 * m2 - right matrix
 * returns 0 on success, -1 on error
 * (dimensions of m1 change if needed)
 */
int m_mul(matrix* m1, const matrix* m2);

/**
 * m = m1 * m2 (matrix multiplication)
 * m - result matrix
 * m1 - left matrix
 * m2 - right matrix
 * returns 0 on success, -1 on error
 */
int m_mul3(matrix* m, const matrix* m1, const matrix* m2);

#endif
