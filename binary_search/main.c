#include "tests.h"
#include <stdio.h>

int main(void) {
    printf("Запуск тестов полиморфного бинарного поиска...\n");
    
    int failed = run_all_tests();
    
    printf("\n=== Итог ===\n");
    if (failed == 0) {
        printf("✓ Все тесты пройдены успешно!\n");
        return 0;
    } else {
        printf("✗ Провалено тестов: %d\n", failed);
        return 1;
    }
}