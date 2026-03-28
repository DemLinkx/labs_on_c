/**
 * @file tests.c
 * @brief UNIT-тесты для полиморфного бинарного поиска.
 * 
 * Тестирует работу bin_search с разными типами данных:
 * - массивы целых чисел
 * - массивы вещественных чисел
 * - массивы строк
 * 
 * Проверяет случаи:
 * - элемент присутствует в массиве
 * - элемент отсутствует, но находится в диапазоне значений
 * - элемент строго меньше первого
 * - элемент строго больше последнего
 */

#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* === Реализация компараторов === */

int int_cmp(const void *a, const void *b) {
    int va = *(const int *)a;
    int vb = *(const int *)b;
    return (va > vb) - (va < vb);
}

int double_cmp(const void *a, const void *b) {
    double va = *(const double *)a;
    double vb = *(const double *)b;
    return (va > vb) - (va < vb);
}

int string_cmp(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

/* === Вспомогательные макросы для тестов === */

#define TEST(name, condition) do { \
    if (condition) { \
        printf("[PASS] %s\n", name); \
    } else { \
        printf("[FAIL] %s\n", name); \
        failed++; \
    } \
} while(0)

/* === Тесты для целых чисел === */

static int test_int_array(void) {
    int failed = 0;
    int arr[] = {1, 3, 5, 7, 9};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    /* Элемент присутствует */
    TEST("int: элемент 5 найден", bin_search(arr, sizeof(int), count, &(int){5}, int_cmp) == 1);
    TEST("int: элемент 1 найден (начало)", bin_search(arr, sizeof(int), count, &(int){1}, int_cmp) == 1);
    TEST("int: элемент 9 найден (конец)", bin_search(arr, sizeof(int), count, &(int){9}, int_cmp) == 1);

    /* Элемент отсутствует, но в диапазоне */
    TEST("int: элемент 4 не найден (между 3 и 5)", bin_search(arr, sizeof(int), count, &(int){4}, int_cmp) == 0);
    TEST("int: элемент 8 не найден (между 7 и 9)", bin_search(arr, sizeof(int), count, &(int){8}, int_cmp) == 0);

    /* Элемент вне диапазона */
    TEST("int: элемент 0 не найден (меньше первого)", bin_search(arr, sizeof(int), count, &(int){0}, int_cmp) == 0);
    TEST("int: элемент 10 не найден (больше последнего)", bin_search(arr, sizeof(int), count, &(int){10}, int_cmp) == 0);

    return failed;
}

/* === Тесты для вещественных чисел === */

static int test_double_array(void) {
    int failed = 0;
    double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    TEST("double: элемент 3.3 найден", bin_search(arr, sizeof(double), count, &(double){3.3}, double_cmp) == 1);
    TEST("double: элемент 1.1 найден (начало)", bin_search(arr, sizeof(double), count, &(double){1.1}, double_cmp) == 1);
    TEST("double: элемент 5.5 найден (конец)", bin_search(arr, sizeof(double), count, &(double){5.5}, double_cmp) == 1);

    TEST("double: элемент 2.5 не найден (внутри)", bin_search(arr, sizeof(double), count, &(double){2.5}, double_cmp) == 0);
    TEST("double: элемент 0.5 не найден (меньше первого)", bin_search(arr, sizeof(double), count, &(double){0.5}, double_cmp) == 0);
    TEST("double: элемент 6.0 не найден (больше последнего)", bin_search(arr, sizeof(double), count, &(double){6.0}, double_cmp) == 0);

    return failed;
}

/* === Тесты для строк === */

static int test_string_array(void) {
    int failed = 0;
    const char *arr[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    const char *target_cherry = "cherry";
    const char *target_blue = "blueberry";
    const char *target_aaa = "aaa";
    const char *target_zebra = "zebra";
    const char *target_apple = "apple";
    const char *target_elder = "elderberry";

    TEST("string: 'cherry' найден", bin_search((void *)arr, sizeof(char *), count, &target_cherry, string_cmp) == 1);
    TEST("string: 'apple' найден (начало)", bin_search((void *)arr, sizeof(char *), count, &target_apple, string_cmp) == 1);
    TEST("string: 'elderberry' найден (конец)", bin_search((void *)arr, sizeof(char *), count, &target_elder, string_cmp) == 1);

    TEST("string: 'blueberry' не найден (внутри)", bin_search((void *)arr, sizeof(char *), count, &target_blue, string_cmp) == 0);
    TEST("string: 'aaa' не найден (меньше первого)", bin_search((void *)arr, sizeof(char *), count, &target_aaa, string_cmp) == 0);
    TEST("string: 'zebra' не найден (больше последнего)", bin_search((void *)arr, sizeof(char *), count, &target_zebra, string_cmp) == 0);

    return failed;
}

/* === Граничные случаи === */

static int test_edge_cases(void) {
    int failed = 0;

    /* Пустой массив */
    int empty[0];
    TEST("edge: пустой массив", bin_search(empty, sizeof(int), 0, &(int){1}, int_cmp) == 0);

    /* Массив из одного элемента — совпадение */
    int single[1] = {42};
    TEST("edge: один элемент, найден", bin_search(single, sizeof(int), 1, &(int){42}, int_cmp) == 1);
    TEST("edge: один элемент, не найден", bin_search(single, sizeof(int), 1, &(int){99}, int_cmp) == 0);

    /* NULL-параметры */
    TEST("edge: NULL массив", bin_search(NULL, sizeof(int), 5, &(int){1}, int_cmp) == 0);
    TEST("edge: NULL искомый элемент", bin_search(single, sizeof(int), 1, NULL, int_cmp) == 0);
    TEST("edge: NULL компаратор", bin_search(single, sizeof(int), 1, &(int){1}, NULL) == 0);

    return failed;
}

/* === Запуск всех тестов === */

int run_all_tests(void) {
    int total_failed = 0;

    printf("\n=== Тесты: целые числа ===\n");
    total_failed += test_int_array();

    printf("\n=== Тесты: вещественные числа ===\n");
    total_failed += test_double_array();

    printf("\n=== Тесты: строки ===\n");
    total_failed += test_string_array();

    printf("\n=== Тесты: граничные случаи ===\n");
    total_failed += test_edge_cases();

    return total_failed;
}