#include "deq.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEQUES 10 

// Глобальные переменные для управления множеством дек
static deque *deques[MAX_DEQUES];
static int deq_count = 0;
static int current_deq_index = -1; // -1 означает, что ни один дек не выбран

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper: Проверка валидности текущего индекса
static int is_current_valid(void) {
    if (current_deq_index < 0 || current_deq_index >= deq_count) {
        printf("Ошибка: Дек не выбран или не существует.\n");
        return 0;
    }
    if (deques[current_deq_index] == NULL) {
        printf("Ошибка: Указатель на текущий дек пуст.\n");
        return 0;
    }
    return 1;
}

// Helper: Вывод списка доступных дек
static void list_deques(void) {
    printf("\n--- Список дек ---\n");
    if (deq_count == 0) {
        printf("Нет созданных дек.\n");
    } else {
        for (int i = 0; i < deq_count; i++) {
            char marker = (i == current_deq_index) ? '>' : ' ';
            printf("%c [%d] ", marker, i);
            if (deques[i]) {
                printf("Size: %d | Content: ", deque_size(deques[i]));
                // Чтобы не засорять вывод, можно печатать только если дек маленький, 
                // или просто писать "..."
                if (deque_size(deques[i]) <= 10) {
                    deque_print(deques[i]);
                } else {
                    printf("[...] (слишком большой для превью)\n");
                }
            } else {
                printf("(NULL)\n");
            }
        }
    }
    printf("------------------\n");
}

int main(void) {
    int choice;
    double val;

    // Инициализация массива нулями
    for (int i = 0; i < MAX_DEQUES; i++) {
        deques[i] = NULL;
    }

    while (1) {
        printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
        printf("0. Создать новый дек\n");
        printf("1. Выбрать активный дек\n");
        printf("2. Удалить текущий дек\n");
        printf("3. List Deques (Список дек)\n");
        printf("--- Операции с активным деком ---\n");
        printf("4. Push Front (добавить в начало)\n");
        printf("5. Push Back  (добавить в конец)\n");
        printf("6. Pop Front  (удалить из начала)\n");
        printf("7. Pop Back   (удалить из конца)\n");
        printf("8. Print      (вывести содержимое)\n");
        printf("9. Size       (размер дека)\n");
        printf("10. Is Empty? (проверка на пустоту)\n");
        printf("11. Copy      (создать копию -> новый дек)\n");
        printf("12. Exit      (освободить ВСЕ деки и выйти)\n");
        
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод.\n");
            clear_stdin();
            continue;
        }
        clear_stdin();

        switch (choice) {
        case 0: { // Создать новый дек
            if (deq_count >= MAX_DEQUES) {
                printf("Достигнут лимит количества дек (%d).\n", MAX_DEQUES);
                break;
            }
            deque *new_d = deq_init();
            if (!new_d) {
                fprintf(stderr, "Ошибка выделения памяти для нового дека.\n");
                break;
            }
            deques[deq_count] = new_d;
            current_deq_index = deq_count; // Автоматически переключаемся на новый
            deq_count++;
            printf("Создан дек #%d. Он теперь активный.\n", current_deq_index);
            break;
        }

        case 1: { // Выбрать активный дек
            list_deques();
            if (deq_count == 0) {
                printf("Сначала создайте дек (пункт 0).\n");
                break;
            }
            printf("Введите номер дека (0-%d): ", deq_count - 1);
            int idx;
            if (scanf("%d", &idx) == 1 && idx >= 0 && idx < deq_count) {
                current_deq_index = idx;
                printf("Активирован дек #%d.\n", current_deq_index);
            } else {
                printf("Неверный номер.\n");
                clear_stdin();
            }
            break;
        }

        case 2: { // Удалить текущий дек
            if (!is_current_valid()) break;
            
            printf("Вы уверены, что хотите удалить дек #%d? (y/n): ", current_deq_index);
            char confirm;
            scanf("%c", &confirm);
            clear_stdin();
            
            if (confirm == 'y' || confirm == 'Y') {
                deque_free(deques[current_deq_index]);
                deques[current_deq_index] = NULL;
                
                for (int i = current_deq_index; i < deq_count - 1; i++) {
                    deques[i] = deques[i+1];
                }
                deques[deq_count - 1] = NULL;
                deq_count--;
                
                if (deq_count == 0) {
                    current_deq_index = -1;
                    printf("Все деки удалены.\n");
                } else {
                    if (current_deq_index >= deq_count) {
                        current_deq_index = deq_count - 1;
                    }
                    printf("Дек удален. Теперь активен дек #%d.\n", current_deq_index);
                }
            } else {
                printf("Удаление отменено.\n");
            }
            break;
        }

        case 3: // List Deques
            list_deques();
            break;

        case 4: { // Push Front
            if (!is_current_valid()) break;
            printf("Введите число: ");
            if (scanf("%lf", &val) == 1) {
                if (deque_push_front(deques[current_deq_index], val) == 0) 
                    printf("ОК\n");
                else 
                    printf("Ошибка выделения памяти.\n");
            } else { 
                printf("Некорректное число.\n"); 
                clear_stdin();
            }
            break;
        }

        case 5: { // Push Back
            if (!is_current_valid()) break;
            printf("Введите число: ");
            if (scanf("%lf", &val) == 1) {
                if (deque_push_back(deques[current_deq_index], val) == 0) 
                    printf("ОК\n");
                else 
                    printf("Ошибка выделения памяти.\n");
            } else { 
                printf("Некорректное число.\n"); 
                clear_stdin();
            }
            break;
        }

        case 6: { // Pop Front
            if (!is_current_valid()) break;
            if (deque_pop_front(deques[current_deq_index], &val) == 0) 
                printf("Удалено из начала: %.2f\n", val);
            else 
                printf("Дек пуст.\n");
            break;
        }

        case 7: { // Pop Back
            if (!is_current_valid()) break;
            if (deque_pop_back(deques[current_deq_index], &val) == 0) 
                printf("Удалено из конца: %.2f\n", val);
            else 
                printf("Дек пуст.\n");
            break;
        }

        case 8: { // Print
            if (!is_current_valid()) break;
            printf("Дек #%d: ", current_deq_index);
            deque_print(deques[current_deq_index]);
            break;
        }

        case 9: { // Size
            if (!is_current_valid()) break;
            printf("Размер дека #%d: %d\n", current_deq_index, deque_size(deques[current_deq_index]));
            break;
        }

        case 10: { // Is Empty
            if (!is_current_valid()) break;
            printf("Дек #%d %s\n", current_deq_index, 
                   deque_is_empty(deques[current_deq_index]) ? "пуст" : "содержит элементы");
            break;
        }

        case 11: { // Copy -> создает новый дек в списке
            if (!is_current_valid()) break;
            deque *copy = deque_copy(deques[current_deq_index]);
            if (copy) {
                if (deq_count >= MAX_DEQUES) {
                    printf("Невозможно создать копию: достигнут лимит дек.\n");
                    deque_free(copy);
                } else {
                    deques[deq_count] = copy;
                    current_deq_index = deq_count;
                    deq_count++;
                    printf("Копия создана как дек #%d и активирована.\n", current_deq_index);
                }
            } else {
                printf("Ошибка копирования.\n");
            }
            break;
        }

        case 12: { // Exit
            printf("Освобождение памяти всех дек...\n");
            for (int i = 0; i < deq_count; i++) {
                if (deques[i] != NULL) {
                    deque_free(deques[i]);
                    deques[i] = NULL;
                }
            }
            deq_count = 0;
            current_deq_index = -1;
            printf("Выход.\n");
            return 0;
        }

        default:
            printf("Неизвестная команда.\n");
        }
    }
}