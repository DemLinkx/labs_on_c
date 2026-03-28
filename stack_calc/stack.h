#ifndef STACK_H
#define STACK_H

#include <stddef.h>


typedef struct Stack Stack;

/**
 * @brief Создать новый пустой стек.
 * 
 * @return Указатель на созданный стек, или NULL при ошибке выделения памяти.
 * 
 * @note Память под стек должна быть освобождена вызовом stack_free().
 */
Stack* stack_create(void);

/**
 * @brief Освободить все ресурсы, занятые стеком.
 * 
 * @param stack Указатель на стек. Если NULL, функция ничего не делает.
 * 
 * @note После вызова этой функции указатель на стек становится невалидным.
 */
void stack_free(Stack* stack);

/**
 * @brief Добавить элемент на вершину стека.
 * 
 * @param stack Указатель на стек.
 * @param value Значение для добавления.
 * @return 0 при успехе, -1 при ошибке (NULL указатель или нехватка памяти).
 */
int stack_push(Stack* stack, double value);

/**
 * @brief Удалить элемент с вершины стека и вернуть его значение.
 * 
 * @param stack Указатель на стек.
 * @param out_value Указатель для сохранения извлечённого значения.
 * @return 0 при успехе, -1 если стек пуст или указатель stack NULL.
 * 
 * @note Если out_value равен NULL, значение всё равно удаляется из стека.
 */
int stack_pop(Stack* stack, double* out_value);

/**
 * @brief Получить значение верхнего элемента без удаления.
 * 
 * @param stack Указатель на стек.
 * @param out_value Указатель для сохранения значения.
 * @return 0 при успехе, -1 если стек пуст или указатели NULL.
 */
int stack_peek(const Stack* stack, double* out_value);

/**
 * @brief Проверить, пуст ли стек.
 * 
 * @param stack Указатель на стек.
 * @return 1 если стек пуст, 0 если содержит элементы.
 */
int stack_is_empty(const Stack* stack);

/**
 * @brief Получить количество элементов в стеке.
 * 
 * @param stack Указатель на стек.
 * @return Количество элементов, 0 если stack NULL.
 */
size_t stack_size(const Stack* stack);

/**
 * @brief Очистить стек (удалить все элементы).
 * 
 * @param stack Указатель на стек.
 * 
 * @note После очистки стек остаётся валидным и может использоваться.
 */
void stack_clear(Stack* stack);

#endif /* STACK_H */