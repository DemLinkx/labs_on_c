#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "ops.h"
#include "manip.h"
#include "tasks.h"
#include <locale.h>

#define EPS 1e-10

static int test_basic_operations(void)
{
    printf("тестирование базовых операций\n");

    matrix* m1 = m_new(2, 2);
    matrix* m2 = m_new(2, 2);

    if (!m1 || !m2) {
        printf("не удалось выделить память под матрицы\n");
        return -1;
    }
    m_set(m1, 0, 0, 1.0);
    m_set(m1, 0, 1, 2.0);
    m_set(m1, 1, 0, 3.0);
    m_set(m1, 1, 1, 4.0);

    matrix* m3 = m_dup(m1);
    if (!m3) {
        printf("не удалось скопировать матрицу\n");
        m_del(m1);
        m_del(m2);
        return -1;
    }

    double val;
    m_get(m3, 0, 0, &val);
    if (fabs(val - 1.0) > EPS) {
        printf("ошибка копирования в позиции (0,0): %f\n", val);
        m_del(m1);
        m_del(m2);
        m_del(m3);
        return -1;
    }

    printf("базовые операции прошли успешно\n");

    m_del(m1);
    m_del(m2);
    m_del(m3);

    return 0;
}

static int test_arithmetic_operations(void)
{
    printf("тестирование арифметических операций\n");

    matrix* a = m_new(2, 2);
    matrix* b = m_new(2, 2);
    matrix* c = m_new(2, 2);

    if (!a || !b || !c) {
        printf("не удалось выделить память под матрицы\n");
        return -1;
    }

    // a = [1 2;
    //      3 4]
    m_set(a, 0, 0, 1.0); m_set(a, 0, 1, 2.0);
    m_set(a, 1, 0, 3.0); m_set(a, 1, 1, 4.0);

    // b = [5 6; 
    // 7 8]
    m_set(b, 0, 0, 5.0); m_set(b, 0, 1, 6.0);
    m_set(b, 1, 0, 7.0); m_set(b, 1, 1, 8.0);

    if (m_add3(c, a, b) != 0) {
        printf("ошибка в m_add3\n");
        m_del(a);
        m_del(b);
        m_del(c);
        return -1;
    }

    double val;
    m_get(c, 0, 0, &val);
    if (fabs(val - 6.0) > EPS) {
        printf("ошибка сложения в позиции (0,0): %f\n", val);
        m_del(a);
        m_del(b);
        m_del(c);
        return -1;
    }

    m_get(c, 1, 1, &val);
    if (fabs(val - 12.0) > EPS) {
        printf("ошибка сложения в позиции (1,1): %f\n", val);
        m_del(a);
        m_del(b);
        m_del(c);
        return -1;
    }

    m_scale2(c, a, 2.0);
    m_get(c, 0, 0, &val);
    if (fabs(val - 2.0) > EPS) {
        printf("Ошибка умножения на скаляр: %f\n", val);
        m_del(a);
        m_del(b);
        m_del(c);
        return -1;
    }

    matrix* d = m_new(2, 2);
    if (!d) {
        printf("не удалось выделить память под матрицу d\n");
        m_del(a);
        m_del(b);
        m_del(c);
        return -1;
    }

    // A * B должно быть [19 22;
    //                    43 50]
    if (m_mul3(d, a, b) != 0) {
        printf("ошибка в m_mul3\n");
        m_del(a);
        m_del(b);
        m_del(c);
        m_del(d);
        return -1;
    }

    m_get(d, 0, 0, &val);
    if (fabs(val - 19.0) > EPS) {
        printf("ошибка умножения в позиции (0,0): %f\n", val);
        m_del(a);
        m_del(b);
        m_del(c);
        m_del(d);
        return -1;
    }

    printf("арифметические операции прошли успешно\n");

    m_del(a);
    m_del(b);
    m_del(c);
    m_del(d);

    return 0;
}

static int test_matrix_manipulations(void)
{
    printf("тестирование манипуляций с матрицами\n");

    matrix* m = m_new(3, 3);
    if (!m) {
        printf("не удалось выделить память под матрицу\n");
        return -1;
    }

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            m_set(m, i, j, i * 3 + j + 1);
        }
    }

    printf("исходная матрица:\n");
    m_print(m);

    m_srow(m, 0, 2);
    double val;
    m_get(m, 0, 0, &val);
    if (fabs(val - 7.0) > EPS) {
        printf("ошибка перестановки строк\n");
        m_del(m);
        return -1;
    }

    m_srow(m, 0, 2);

    m_scol(m, 0, 2);
    m_get(m, 0, 0, &val);
    if (fabs(val - 3.0) > EPS) {
        printf("ошибка перестановки столбцов\n");
        m_del(m);
        return -1;
    }

    m_scol(m, 0, 2);

    m_tr(m);
    m_get(m, 0, 1, &val);
    if (fabs(val - 4.0) > EPS) {
        printf("ошибка транспонирования\n");
        m_del(m);
        return -1;
    }

    double norm = m_norm(m);
    if (fabs(norm - 18.0) > EPS) {
        printf("ошибка вычисления нормы: %f\n", norm);
        m_del(m);
        return -1;
    }

    printf("манипуляции с матрицами прошли успешно\n");

    m_del(m);
    return 0;
}

static int test_m_exp_diagonal(void)
{
    printf("тестирование матричной экспоненты на диагональной матрице\n");

    matrix* a = m_new(3, 3);
    if (!a) {
        printf("не удалось выделить память под матрицу\n");
        return -1;
    }

    m_zero(a);
    m_set(a, 0, 0, 1.0);
    m_set(a, 1, 1, 2.0);
    m_set(a, 2, 2, -1.0);

    printf("A = \n");
    m_print(a);

    matrix* exp_a = m_exp(a, 1e-8);
    if (!exp_a) {
        printf("m_exp вернула NULL\n");
        m_del(a);
        return -1;
    }

    printf("exp(A) = \n");
    m_print(exp_a);

    double val;
    m_get(exp_a, 0, 0, &val);
    if (fabs(val - exp(1.0)) > 1e-6) {
        printf("ошибка exp(1): %f\n", val);
        m_del(a);
        m_del(exp_a);
        return -1;
    }

    m_get(exp_a, 1, 1, &val);
    if (fabs(val - exp(2.0)) > 1e-6) {
        printf("ошибка exp(2): %f\n", val);
        m_del(a);
        m_del(exp_a);
        return -1;
    }

    m_get(exp_a, 2, 2, &val);
    if (fabs(val - exp(-1.0)) > 1e-6) {
        printf("ошибка exp(-1): %f\n", val);
        m_del(a);
        m_del(exp_a);
        return -1;
    }

    m_get(exp_a, 0, 1, &val);
    if (fabs(val) > 1e-10) {
        printf("недиагональный элемент не равен нулю: %f\n", val);
        m_del(a);
        m_del(exp_a);
        return -1;
    }

    printf("тест матричной экспоненты пройден успешно\n");

    m_del(a);
    m_del(exp_a);

    return 0;
}

static int test_gaussian_elimination(void)
{
    printf("тестирование метода Гаусса\n");

    matrix* a1 = m_new(2, 2);
    matrix* b1 = m_new(1, 2);
    matrix* x1 = m_new(1, 2);

    if (!a1 || !b1 || !x1) {
        printf("не удалось выделить память под матрицы для системы 1\n");
        m_del(a1);
        m_del(b1);
        m_del(x1);
        return -1;
    }

    m_set(a1, 0, 0, 2.0); m_set(a1, 0, 1, 1.0);
    m_set(a1, 1, 0, 1.0); m_set(a1, 1, 1, -1.0);
    m_set(b1, 0, 0, 5.0);
    m_set(b1, 1, 0, 1.0);

    printf("система 1:\n");
    printf("2x + y = 5\n");
    printf("x - y = 1\n");

    if (m_solve(a1, b1, x1) != 0) {
        printf("не удалось решить систему 1\n");
        m_del(a1);
        m_del(b1);
        m_del(x1);
        return -1;
    }

    double x, y;
    m_get(x1, 0, 0, &x);
    m_get(x1, 1, 0, &y);

    printf("решение: x = %f, y = %f\n", x, y);

    if (fabs(x - 2.0) > 1e-8 || fabs(y - 1.0) > 1e-8) {
        printf("неверное решение для системы 1\n");
        m_del(a1);
        m_del(b1);
        m_del(x1);
        return -1;
    }

    matrix* r1 = m_new(1, 2);
    matrix* ax1 = m_new(1, 2);

    m_mul3(ax1, a1, x1);
    m_sub3(r1, ax1, b1);

    double norm_r = m_norm(r1);
    printf("норма невязки: %e\n", norm_r);

    if (norm_r > 1e-10) {
        printf("слишком большое расхождение: %e\n", norm_r);
        m_del(a1);
        m_del(b1);
        m_del(x1);
        m_del(r1);
        m_del(ax1);
        return -1;
    }

    m_del(r1);
    m_del(ax1);

    matrix* a2 = m_new(3, 3);
    matrix* b2 = m_new(1, 3);
    matrix* x2 = m_new(1, 3);

    if (!a2 || !b2 || !x2) {
        printf("не удалось выделить память под матрицы для системы 2\n");
        m_del(a1);
        m_del(b1);
        m_del(x1);
        m_del(a2);
        m_del(b2);
        m_del(x2);
        return -1;
    }

    // 2x + y + z = 5
    // x + 2y + z = 6
    // x + y + 2z = 7
    m_set(a2, 0, 0, 2.0); m_set(a2, 0, 1, 1.0); m_set(a2, 0, 2, 1.0);
    m_set(a2, 1, 0, 1.0); m_set(a2, 1, 1, 2.0); m_set(a2, 1, 2, 1.0);
    m_set(a2, 2, 0, 1.0); m_set(a2, 2, 1, 1.0); m_set(a2, 2, 2, 2.0);

    m_set(b2, 0, 0, 5.0);
    m_set(b2, 1, 0, 6.0);
    m_set(b2, 2, 0, 7.0);

    printf("\nсистема 2:\n");
    printf("2x + y + z = 5\n");
    printf("x + 2y + z = 6\n");
    printf("x + y + 2z = 7\n");

    if (m_solve(a2, b2, x2) != 0) {
        printf("не удалось решить систему 2\n");
        m_del(a1);
        m_del(b1);
        m_del(x1);
        m_del(a2);
        m_del(b2);
        m_del(x2);
        return -1;
    }

    double x2_val, y2_val, z2_val;
    m_get(x2, 0, 0, &x2_val);
    m_get(x2, 1, 0, &y2_val);
    m_get(x2, 2, 0, &z2_val);

    printf("решение: x = %f, y = %f, z = %f\n", x2_val, y2_val, z2_val);

    if (fabs(x2_val - 0.5) > 1e-8 || fabs(y2_val - 1.5) > 1e-8 || fabs(z2_val - 2.5) > 1e-8) {
        printf("неверное решение для системы 2\n");
        m_del(a1);
        m_del(b1);
        m_del(x1);
        m_del(a2);
        m_del(b2);
        m_del(x2);
        return -1;
    }

    matrix* r2 = m_new(1, 3);
    matrix* ax2 = m_new(1, 3);

    m_mul3(ax2, a2, x2);
    m_sub3(r2, ax2, b2);

    norm_r = m_norm(r2);
    printf("норма невязки для системы 2: %e\n", norm_r);

    if (norm_r > 1e-10) {
        printf("слишком большое расхождение для системы 2: %e\n", norm_r);
        m_del(a1);
        m_del(b1);
        m_del(x1);
        m_del(a2);
        m_del(b2);
        m_del(x2);
        m_del(r2);
        m_del(ax2);
        return -1;
    }

    m_del(r2);
    m_del(ax2);

    m_del(a1);
    m_del(b1);
    m_del(x1);
    m_del(a2);
    m_del(b2);
    m_del(x2);

    printf("тесты метода Гаусса пройдены успешно\n");

    return 0;
}

static int test_gaussian_permuted(void)
{
    printf("тест с переставленными уравнениями\n");

    // 0x + 0y + 1z = 1 => z = 1
    // 0x + 1y + 0z = 2 => y = 2
    // 1x + 0y + 0z = 3 => x = 3

    matrix* a = m_new(3, 3);
    matrix* b = m_new(1, 3);
    matrix* x = m_new(1, 3);

    if (!a || !b || !x) {
        printf("не удалось выделить память под матрицу\n");
        m_del(a);
        m_del(b);
        m_del(x);
        return -1;
    }

    m_set(a, 0, 0, 0.0); m_set(a, 0, 1, 0.0); m_set(a, 0, 2, 1.0);
    m_set(a, 1, 0, 0.0); m_set(a, 1, 1, 1.0); m_set(a, 1, 2, 0.0);
    m_set(a, 2, 0, 1.0); m_set(a, 2, 1, 0.0); m_set(a, 2, 2, 0.0);

    m_set(b, 0, 0, 1.0);
    m_set(b, 1, 0, 2.0);
    m_set(b, 2, 0, 3.0);

    printf("система:\n");
    printf("0x + 0y + 1z = 1\n");
    printf("0x + 1y + 0z = 2\n");
    printf("1x + 0y + 0z = 3\n");

    if (m_solve(a, b, x) != 0) {
        printf("не удалось решить систему\n");
        m_del(a);
        m_del(b);
        m_del(x);
        return -1;
    }

    double x_val, y_val, z_val;
    m_get(x, 0, 0, &x_val);
    m_get(x, 1, 0, &y_val);
    m_get(x, 2, 0, &z_val);

    printf("решение: x = %f, y = %f, z = %f\n", x_val, y_val, z_val);

    if (fabs(x_val - 3.0) > 1e-8 ||
        fabs(y_val - 2.0) > 1e-8 ||
        fabs(z_val - 1.0) > 1e-8) {
        printf("неверное решение\n");
        m_del(a);
        m_del(b);
        m_del(x);
        return -1;
    }

    matrix* ax = m_new(1, 3);
    matrix* r = m_new(1, 3);

    m_mul3(ax, a, x);
    m_sub3(r, ax, b);

    double norm_r = m_norm(r);
    printf("норма невязки: %e\n", norm_r);

    m_del(ax);
    m_del(r);
    m_del(a);
    m_del(b);
    m_del(x);

    if (norm_r > 1e-10) {
        printf("слишком большое расхождение\n");
        return -1;
    }

    printf("тест с переставленными уравнениями пройден\n");
    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "rus");

    printf("ТЕСТИРОВАНИЕ МАТРИЦ\n");

    int tests_passed = 0;
    int total_tests = 6;

    if (test_basic_operations() == 0) {
        printf("тест базовых операций пройден\n");
        tests_passed++;
    }
    else {
        printf("тест базовых операций не пройден\n");
    }

    printf("\n");

    if (test_arithmetic_operations() == 0) {
        printf("тест арифметических операций пройден\n");
        tests_passed++;
    }
    else {
        printf("тест арифметических операций не пройден\n");
    }

    printf("\n");

    if (test_matrix_manipulations() == 0) {
        printf("тест манипуляций с матрицами пройден\n");
        tests_passed++;
    }
    else {
        printf("тест манипуляций с матрицами не пройден\n");
    }

    printf("\n");

    if (test_m_exp_diagonal() == 0) {
        printf("тест матричной экспоненты пройден\n");
        tests_passed++;
    }
    else {
        printf("тест матричной экспоненты не пройден\n");
    }

    printf("\n");

    if (test_gaussian_elimination() == 0) {
        printf("тест метода Гаусса пройден\n");
        tests_passed++;
    }
    else {
        printf("тест метода Гаусса не пройден\n");
    }
    if (test_gaussian_permuted() == 0) {    
        printf("тест метода Гаусса с переставленными уравненими пройден\n");
        tests_passed++;
    }
    else {
        printf("тест метода Гаусса с переставленными уравнениями не пройден\n");
    }

    printf("ИТОГ:\n");
    printf("пройдено %d/%d тестов\n", tests_passed, total_tests);

    if (tests_passed == total_tests) {
        printf("все тесты успешно пройдены\n");
        return 0;
    }
    else {
        printf("некоторые тесты не пройдены\n");
        return 1;
    }
}