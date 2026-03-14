#include <stdio.h>

#ifndef binary_place
#define binary_place


/* args:
 * array -- указатель на массив целых чисел (отсортированный)
 * n -- размер массива
 * el -- целое число, для которого ищем индекс
 * 
 * return:
 * возвращает правый индекс в массиве, на который 
 * можно поставить el, чтобы массив остался отсортированным
 */
size_t bin_place(const int *array, size_t n, int el);

#endif
