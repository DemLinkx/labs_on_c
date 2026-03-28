
#ifndef TESTS_H
#define TESTS_H

#include "bin_s.h"

/**
 * запускает все тесты и возвращает количество неудачных тестов.
 */
int run_all_tests(void);

/* === Вспомогательные функции сравнения для тестов === */

/** Сравнение целых чисел */
int int_cmp(const void *a, const void *b);

/** Сравнение чисел с плавающей точкой (double) */
int double_cmp(const void *a, const void *b);

/** Сравнение строк */
int string_cmp(const void *a, const void *b);

#endif /* TESTS_H */