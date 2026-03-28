#include "deq.h"
#include <stdio.h>

int main(void) {
    printf("=== Пример работы с деком ===\n\n");
    
    // 1. Создаём дек
    deque *d = deq_init();
    printf("1. Создан новый дек: ");
    deque_print(d);
    
    // 2. Добавляем элементы
    deque_push_back(d, 10.5);
    deque_push_back(d, 20.3);
    deque_push_back(d, 30.7);
    printf("2. Добавили 10.5, 20.3, 30.7 в конец: ");
    deque_print(d);
    
    // 3. Добавляем в начало
    deque_push_front(d, 5.0);
    printf("3. Добавили 5.0 в начало: ");
    deque_print(d);
    
    // 4. Удаляем из начала
    double val;
    deque_pop_front(d, &val);
    printf("4. Удалили из начала (%.2f): ", val);
    deque_print(d);
    
    // 5. Удаляем из конца
    deque_pop_back(d, &val);
    printf("5. Удалили из конца (%.2f): ", val);
    deque_print(d);
    
    // 6. Копируем дек
    deque *d_copy = deque_copy(d);
    printf("6. Создали копию: ");
    deque_print(d_copy);
    
    // 7. Показываем размеры
    printf("7. Размер оригинала: %d, копии: %d\n", 
           deque_size(d), deque_size(d_copy));
    
    // 8. Проверяем на пустоту
    printf("8. Дек %s\n", 
           deque_is_empty(d) ? "пуст" : "не пуст");
    
    // 9. Освобождаем память
    deque_free(d);
    deque_free(d_copy);
    printf("9. Память освобождена\n");
    
    printf("\n=== Готово ===\n");
    return 0;
}