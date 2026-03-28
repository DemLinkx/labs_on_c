#ifndef BIN_S_H
#define BIN_S_H

#include <stddef.h>

/**
 * @brief Тип функции сравнения двух элементов.
 * 
 * @param el1 Указатель на первый элемент.
 * @param el2 Указатель на второй элемент.
 * @return <0 если el1 < el2, 0 если равны, >0 если el1 > el2.
 */
typedef int (*cmp_t)(const void *el1, const void *el2);

/**
 * @brief Выполняет бинарный поиск элемента в отсортированном массиве.
 * 
 * @param array Указатель на начало массива.
 * @param size Размер одного элемента в байтах.
 * @param count Количество элементов в массиве.
 * @param el Указатель на искомый элемент.
 * @param cmp Функция сравнения элементов.
 * @return 1 если элемент найден, 0 если не найден.
 * 
 * @note Массив должен быть отсортирован в порядке, согласованном с функцией cmp.
 * @note Использует арифметику указателей с учётом размера элемента.
 */
int bin_search(void *array, size_t size, size_t count, const void *el, cmp_t cmp);

#endif /* BIN_S_H */