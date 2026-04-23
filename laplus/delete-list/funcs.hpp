#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>

struct point {
    int x, y;
};

// По идее достаточно определить только operator<
inline bool operator<(const point& p1, const point& p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

// Перегрузка вывода в поток для удобного тестирования
inline std::ostream& operator<<(std::ostream& os, const point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// Задача 1: адаптированный "пузырёк"
template <typename T>
void sort(T* arr, size_t n) {
    if (n <= 1) return;
    
    T* now = arr;
    while (now < arr + n - 1) {
        if (*(now + 1) < *now) {
            T temp = *now;
            *now = *(now + 1);
            *(now + 1) = temp;
            now = arr;
        } else {
            now++;
        }
    }
}

// Задача 2: Удаление элементов по предикату
template <typename T, typename P>
void remove_if(T* arr, size_t& n, P pred) {
    T* i = arr;
    while (i < arr + n) {
        if (pred(*i)) {
            T* j = i;
            while (j < arr + n - 1) {
                *j = *(j + 1);
                j++;
            }
            n--; 
        } else {
            i++; 
        }
    }
}

// Вспомогательная функция для печати массивов любого типа
template <typename T>
void print_array(const char* name, const T* arr, size_t n) {
    std::cout << name << " [" << n << "]: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    std::cout << "\n";
}

#endif