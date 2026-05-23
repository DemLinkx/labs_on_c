#include "img.hpp"
#include <iostream>

using namespace std;

// Вспомогательная функция для разделения тестов
void printSeparator(const string& title) {
    cout << "\n========================================\n";
    cout << " TEST: " << title << "\n";
    cout << "========================================\n";
}

int main() {
    printSeparator("1. Конструктор и вывод (operator<<)");
    cout << "Создаем изображение 800x600 (по умолчанию пропорции сохранены):" << endl;
    Image img1(800, 600);
    cout << "Текущее состояние: " << img1 << endl;

    cout << "\nСоздаем изображение с некорректными размерами (0x0):" << endl;
    Image imgInvalid(0, 0); 
    cout << "Текущее состояние: " << imgInvalid << endl;


    printSeparator("2. Геттеры (getWidth, getHeight)");
    cout << "Ширина img1: " << img1.getWidth() << endl;
    cout << "Высота img1: " << img1.getHeight() << endl;


    printSeparator("3. Изменение размеров БЕЗ сохранения пропорций");
    img1.setProportionsMode(false);
    cout << "Режим изменен на: БЕЗ сохранения пропорций." << endl;
    
    cout << "Устанавливаем ширину 1920:" << endl;
    img1.setWidth(1920);
    cout << "Состояние: " << img1 << endl; 

    cout << "Устанавливаем высоту 1080:" << endl;
    img1.setHeight(1080);
    cout << "Состояние: " << img1 << endl;

    printSeparator("4. Изменение размеров С сохранением пропорций");
    Image img2(800, 600); 
    cout << "Исходное: " << img2 << endl;
    img2.setProportionsMode(true);
    cout << "Режим изменен на: С сохранением пропорций." << endl;

    cout << "Меняем ширину на 400 (должно быть 4:3 -> высота ~300):" << endl;
    img2.setWidth(400);
    cout << "Состояние: " << img2 << endl;

    cout << "Меняем высоту на 200 (должно быть 4:3 -> ширина ~267):" << endl;
    img2.setHeight(200);
    cout << "Состояние: " << img2 << endl;

    // 5. Метод "Вписать в рамку" (Fit to Frame)
    printSeparator("5. Метод 'Вписать в рамку' (fitToFrame)");
    
    // 5a. С сохранением пропорций
    Image img3(1920, 1080); // 16:9
    cout << "Исходное: " << img3 << endl;
    cout << "Вписываем в рамку 800x600 (пропорции сохранены):" << endl;
    img3.fitToFrame(800, 600); 
    cout << "Состояние: " << img3 << endl;

    // 5b. Без сохранения пропорций
    Image img4(1920, 1080);
    img4.setProportionsMode(false);
    cout << "\nИсходное: " << img4 << endl;
    cout << "Режим: БЕЗ сохранения пропорций." << endl;
    cout << "Вписываем в рамку 800x600 (пропорции искажаются):" << endl;
    img4.fitToFrame(800, 600);
    cout << "Состояние: " << img4 << endl;

    printSeparator("6. Динамическое переключение режимов");
    Image img5(1000, 500); // 2:1
    cout << "Исходное: " << img5 << endl;
    
    cout << "1. Меняем ширину на 2000 (режим KEEP):" << endl;
    img5.setProportionsMode(true);
    img5.setWidth(2000); 
    // Высота должна стать 1000
    cout << "Состояние: " << img5 << endl;

    cout << "2. Переключаем в режим NO KEEP и меняем высоту на 300:" << endl;
    img5.setProportionsMode(false);
    img5.setHeight(300);
    cout << "Состояние: " << img5 << endl;

    cout << "3. Снова включаем KEEP и вписываем в 100x100:" << endl;
    img5.setProportionsMode(true);
    img5.fitToFrame(100, 100);
   
    cout << "Состояние: " << img5 << endl;

    printSeparator("7. Валидация ввода (отрицательные и нулевые значения)");
    Image img6(100, 100);
    cout << "Исходное: " << img6 << endl;
    
    cout << "Пытаемся установить высоту -50:" << endl;
    img6.setHeight(-50);
    cout << "Состояние: " << img6 << endl;

    cout << "Пытаемся установить ширину 0:" << endl;
    img6.setWidth(0); 
    cout << "Состояние: " << img6 << endl;

    cout << "\nВсе тесты завершены." << endl;

    return 0;
}