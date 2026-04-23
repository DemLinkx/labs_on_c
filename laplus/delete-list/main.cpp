#include <iostream>
#include "funcs.hpp"


// Предикаты для типа int
bool is_even(int x) { return x % 2 == 0; }
bool is_negative(int x) { return x < 0; }
bool is_greater_than_5(int x) { return x > 5; }


// Предикаты для типа point
bool is_on_x_axis(point p) { return p.y == 0; }
bool has_negative_coord(point p) { return p.x < 0 || p.y < 0; }


// Тесты сортировки
void test_sort_int() {
    std::cout << "\n=== Тест сортировки (int) ===\n";
    size_t n = 6;
    int* arr = new int[n]{5, -2, 9, 1, 4, -8};
    
    print_array("Исходный", arr, n);
    sort(arr, n);
    print_array("Отсортированный", arr, n);
    
    delete[] arr;
}

void test_sort_double() {
    std::cout << "\n=== Тест сортировки (double) ===\n";
    size_t n = 5;
    double* arr = new double[n]{3.141592653589793, 2.7182818284590452, 4.2, 2.2, 0.5};
    
    print_array("Исходный", arr, n);
    sort(arr, n);
    print_array("Отсортированный", arr, n);
    
    delete[] arr;
}

void test_sort_point() {
    std::cout << "\n=== Тест сортировки (point) ===\n";
    size_t n = 4;
    point* arr = new point[n]{{2, 5}, {1, 3}, {1, 1}, {3, 0}};
    
    print_array("Исходный", arr, n);
    sort(arr, n);
    print_array("Отсортированный", arr, n);
    
    delete[] arr;
}

// Тесты remove_if
void test_remove_if_int() {
    std::cout << "\n=== Тест remove_if (int) ===\n";
    size_t n = 8;
    int* arr = new int[n]{1, 2, -3, 4, -5, 6, 7, -8};
    
    print_array("Исходный", arr, n);
    
    // Удаляем отрицательные числа
    remove_if(arr, n, is_negative);
    print_array("После удаления отрицательных", arr, n);
    
    // Удаляем чётные числа из оставшихся
    remove_if(arr, n, is_even);
    print_array("После удаления чётных", arr, n);
    
    delete[] arr;
}

void test_remove_if_point() {
    std::cout << "\n=== Тест remove_if (point) ===\n";
    size_t n = 6;
    point* arr = new point[n]{
        {0, 0}, {2, -1}, {-3, 4}, {5, 5}, {0, 7}, {-1, -2}
    };
    
    print_array("Исходный", arr, n);
    
    // Удаляем точки на оси X (y == 0)
    remove_if(arr, n, is_on_x_axis);
    print_array("После удаления точек на оси X", arr, n);
    
    // Удаляем точки с хотя бы одной отрицательной координатой
    remove_if(arr, n, has_negative_coord);
    print_array("После удаления точек с отриц. координатами", arr, n);
    
    delete[] arr;
}


int main() {
    // Тесты сортировки
    test_sort_int();
    test_sort_double();
    test_sort_point();
    
    // Тесты фильтрации
    test_remove_if_int();
    test_remove_if_point();
    
    return 0;
}