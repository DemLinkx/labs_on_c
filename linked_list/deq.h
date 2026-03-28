#ifndef DEQUE_H
#define DEQUE_H

#include <stdlib.h>


/**
 * @file deque.h
 * @brief Двусвязный список (дек)
 */


typedef struct deque deque;

/** Инициализация пустого дека */
deque *deq_init(void);

/** Освобождение памяти */
void deque_free(deque *d);

/** Копирование дека */
deque *deque_copy(deque *d);

/** Добавить в начало */
int deque_push_front(deque *d, double data);

/** Добавить в конец */
int deque_push_back(deque *d, double data);

/** Удалить из конца */
int deque_pop_back(deque *d, double *data);

/** Удалить из начала */
int deque_pop_front(deque *d, double *data);

/** Проверка на пустоту */
int deque_is_empty(deque *d);

/** Вывод дека */
void deque_print(deque *d);

/** Размер дека */
int deque_size(deque *d);

#endif