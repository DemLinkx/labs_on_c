#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <iostream>

class Image {
private:
    int height;
    int width;
    bool keepProportions; 

    // Вспомогательный метод для проверки корректности размера
    bool isValidSize(int size) const;

    // Вспомогательный метод для обновления размеров с сохранением пропорций
    void updateWithProportions(int newHeight, int newWidth, bool changeHeight);

public:
    // Конструктор
    Image(int h = 1, int w = 1);

    // Геттеры
    int getHeight() const;
    int getWidth() const;

    // Методы изменения размеров
    void setHeight(int newHeight);
    void setWidth(int newWidth);

    // Метод "вписать в рамку"
    void fitToFrame(int frameWidth, int frameHeight);

    // Метод изменения режима
    void setProportionsMode(bool keep);

    // Метод получения текущего режима
    bool getProportionsMode() const;

    // Дружественная функция для перегрузки оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Image& img);
};



#endif // IMAGE_H_INCLUDED