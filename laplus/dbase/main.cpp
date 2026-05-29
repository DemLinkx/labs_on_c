#include "database.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <limits>

using namespace std;

// --- Вспомогательные функции ---

// Очистка буфера ввода (чтобы cin не пропускал строки)
void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Безопасный ввод строки
string get_string_input(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Безопасный ввод числа
int get_int_input(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            clear_input_buffer();
            return val;
        } else {
            clear_input_buffer();
            cout << "Ошибка: введите корректное число.\n";
        }
    }
}

// --- Логика меню ---

void print_banner() {
    cout << "\n+------------------------------------------+" << endl;
    cout << "|          LAB DATABASE SYSTEM v1.0          |" << endl;
    cout << "+------------------------------------------+\n" << endl;
}

int main() {
    unique_ptr<DataBase> db; // Текущая база данных
    string active_table_name = ""; // Имя таблицы, с которой работаем

    print_banner();

    while (true) {
        cout << "=== ГЛАВНОЕ МЕНЮ ===" << endl;

        if (db) {
            cout << "[+] База данных: " << db->get_name() << " (Активна)" << endl;
            cout << "    Таблиц: " << (db->get_table("dummy") ? 0 : 0) << endl; // Хак для проверки, лучше добавить метод в DB
            // Выведем список таблиц вручную, так как нет публичного метода list_tables
            // Но мы можем использовать print_structure, чтобы просто показать
            cout << "Структура БД:" << endl;
            db->print_structure();
            cout << "----------------------------------------" << endl;
        } else {
            cout << "[-] База данных не загружена" << endl;
        }
        cout << "========================================" << endl;

        // Если БД открыта, показываем расширенное меню
        if (db) {
            cout << "1. Создать новую таблицу" << endl;
            cout << "2. Выбрать таблицу для работы" << endl;
            
            if (!active_table_name.empty()) {
                cout << "3. Добавить столбец в '" << active_table_name << "'" << endl;
                cout << "4. Добавить строку в '" << active_table_name << "'" << endl;
                cout << "5. Печать таблицы '" << active_table_name << "'" << endl;
                cout << "6. Сортировка таблицы '" << active_table_name << "'" << endl;
                cout << "7. Удалить строку из '" << active_table_name << "'" << endl;
            } else {
                cout << "(Сначала выберите таблицу (п.2))" << endl;
            }

            cout << "8. Сохранить БД в файл" << endl;
            cout << "9. Закрыть БД" << endl;
        } else {
            cout << "1. Создать новую БД" << endl;
            cout << "2. Загрузить БД из файла" << endl;
        }

        cout << "0. Выход" << endl;
        cout << ">> ";

        int choice;
        if (!(cin >> choice)) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        try {
            if (choice == 0) {
                cout << "Выход из программы..." << endl;
                break;
            }

            // --- БЛОК: Нет открытой БД ---
            if (!db) {
                if (choice == 1) {
                    string name = get_string_input("Введите имя новой базы данных: ");
                    if (!name.empty()) {
                        db = make_unique<DataBase>(name);
                        cout << "База данных '" << name << "' создана.\n";
                    }
                } else if (choice == 2) {
                    string filename = get_string_input("Введите имя файла для загрузки: ");
                    auto loaded_db = DataBase::load_new(filename);
                    if (loaded_db) {
                        db = std::move(loaded_db);
                        cout << "База данных загружена из файла.\n";
                    } else {
                        cout << "Ошибка загрузки файла.\n";
                    }
                }
            } 
            else {
                if (choice == 1) { // Создать таблицу
                    string t_name = get_string_input("Введите имя новой таблицы: ");
                    if (!t_name.empty()) {
                        try {
                            db->create_table(t_name);
                            cout << "Таблица '" << t_name << "' создана.\n";
                            active_table_name = t_name; // Сразу выбираем её
                        } catch (const exception& e) {
                            cout << "Ошибка: " << e.what() << "\n";
                        }
                    }
                }
                else if (choice == 2) { // Выбрать таблицу
                    db->print_structure();
                    string t_name = get_string_input("Введите имя таблицы для выбора: ");
                    if (db->get_table(t_name)) {
                        active_table_name = t_name;
                        cout << "Выбрана таблица: " << t_name << "\n";
                    } else {
                        cout << "Таблица не найдена.\n";
                    }
                }
                else if (choice == 3 && !active_table_name.empty()) { // Добавить столбец
                    Table* tbl = db->get_table(active_table_name);
                    if (!tbl) { cout << "Ошибка выбора таблицы.\n"; continue; }

                    string col_name = get_string_input("Имя столбца: ");
                    cout << "Выберите тип:\n1. int\n2. double\n3. string\n>> ";
                    int type_choice;
                    cin >> type_choice;
                    clear_input_buffer();

                    if (type_choice == 1) tbl->add_column<int>(col_name);
                    else if (type_choice == 2) tbl->add_column<double>(col_name);
                    else if (type_choice == 3) tbl->add_column<string>(col_name);
                    else { cout << "Неверный тип.\n"; continue; }

                    cout << "Столбец добавлен.\n";
                }
                else if (choice == 4 && !active_table_name.empty()) { // Добавить строку
                    Table* tbl = db->get_table(active_table_name);
                    if (!tbl) { cout << "Ошибка выбора таблицы.\n"; continue; }
                    if (tbl->column_count() == 0) {
                        cout << "В таблице нет столбцов. Сначала добавьте столбцы.\n";
                        continue;
                    }

                    vector<string> row_data;
                    cout << "Введите данные для " << tbl->column_count() << " столбцов:\n";
                    for (size_t i = 0; i < tbl->column_count(); ++i) {
                        string val = get_string_input("  Значение [" + to_string(i+1) + "]: ");
                        row_data.push_back(val);
                    }

                    if (tbl->add_row(row_data)) {
                        cout << "Строка добавлена.\n";
                    } else {
                        cout << "Ошибка добавления строки.\n";
                    }
                }
                else if (choice == 5 && !active_table_name.empty()) { // Печать
                    Table* tbl = db->get_table(active_table_name);
                    if (tbl) tbl->print();
                }
                else if (choice == 6 && !active_table_name.empty()) { // Сортировка
                    Table* tbl = db->get_table(active_table_name);
                    if (!tbl) continue;
                    
                    string col_name = get_string_input("Сортировать по столбцу (имя): ");
                    bool asc = (get_string_input("По возрастанию (y/n): ") == "y");
                    tbl->sort_by_column_name(col_name, asc);
                    cout << "Сортировка выполнена.\n";
                }
                else if (choice == 7 && !active_table_name.empty()) { // Удалить строку
                    Table* tbl = db->get_table(active_table_name);
                    if (!tbl) continue;
                    int idx = get_int_input("Индекс удаляемой строки (0...): ");
                    if (idx >= 0 && idx < tbl->row_count()) {
                        tbl->remove_row(idx);
                        cout << "Строка удалена.\n";
                    } else {
                        cout << "Неверный индекс.\n";
                    }
                }
                else if (choice == 8) { // Сохранить
                    string filename = get_string_input("Введите имя файла для сохранения: ");
                    if (db->save(filename)) {
                        cout << "Сохранено успешно.\n";
                    } else {
                        cout << "Ошибка сохранения.\n";
                    }
                }
                else if (choice == 9) { // Закрыть
                    db.reset();
                    active_table_name = "";
                    cout << "База данных закрыта.\n";
                }
                else {
                    cout << "Неверный выбор или действие недоступно.\n";
                }
            }

        } catch (const exception& e) {
            cout << "\n[ИСКЛЮЧЕНИЕ]: " << e.what() << "\n";
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.get();
    }

    return 0;
}