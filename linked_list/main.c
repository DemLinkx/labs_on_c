#include "deq.h"
#include <stdio.h>
#include <stdlib.h>

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    deque *d = deq_init();
    if (!d) {
        fprintf(stderr, "Ошибка инициализации памяти\n");
        return 1;
    }

    int choice;
    double val;

    while (1) {
        printf("\n=== МЕНЮ ДЕКА ===\n");
        printf("1. Push Front (добавить в начало)\n");
        printf("2. Push Back  (добавить в конец)\n");
        printf("3. Pop Front  (удалить из начала)\n");
        printf("4. Pop Back   (удалить из конца)\n");
        printf("5. Print      (вывести содержимое)\n");
        printf("6. Size       (размер дека)\n");
        printf("7. Is Empty?  (проверка на пустоту)\n");
        printf("8. Copy       (создать и вывести копию)\n");
        printf("9. Exit       (освободить память и выйти)\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод.\n");
            clear_stdin();
            continue;
        }
        clear_stdin();

        switch (choice) {
            case 1: {
                printf("Введите число: ");
                if (scanf("%lf", &val) == 1) {
                    if (deque_push_front(d, val) == 0) printf("ОК\n");
                    else printf("Ошибка выделения памяти.\n");
                } else { printf("Некорректное число.\n"); }
                clear_stdin();
                break;
            }
            case 2: {
                printf("Введите число: ");
                if (scanf("%lf", &val) == 1) {
                    if (deque_push_back(d, val) == 0) printf("ОК\n");
                    else printf("Ошибка выделения памяти.\n");
                } else { printf("Некорректное число.\n"); }
                clear_stdin();
                break;
            }
            case 3:
                if (deque_pop_front(d, &val) == 0) printf("Удалено из начала: %.2f\n", val);
                else printf("Дек пуст.\n");
                break;
            case 4:
                if (deque_pop_back(d, &val) == 0) printf("Удалено из конца: %.2f\n", val);
                else printf("Дек пуст.\n");
                break;
            case 5:
                deque_print(d);
                break;
            case 6:
                printf("Размер: %d\n", deque_size(d));
                break;
            case 7:
                printf("Дек %s\n", deque_is_empty(d) ? "пуст" : "содержит элементы");
                break;
            case 8: {
                deque *copy = deque_copy(d);
                if (copy) {
                    printf("Копия: ");
                    deque_print(copy);
                    deque_free(copy);
                } else {
                    printf("Ошибка копирования.\n");
                }
                break;
            }
            case 9:
                deque_free(d);
                printf("Память освобождена. Выход.\n");
                return 0;
            default:
                printf("Неизвестная команда.\n");
        }
    }
}