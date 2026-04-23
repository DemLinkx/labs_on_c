#include "acc.hpp"
#include <limits>
#include <string>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMenu() {
    std::cout << "\n========== БАНКОВСКИЙ СЧЁТ ==========\n";
    std::cout << "1. Пополнить баланс\n";
    std::cout << "2. Снять деньги\n";
    std::cout << "3. Заблокировать счёт (с причиной)\n";
    std::cout << "4. Заблокировать счёт без причины (только при 666)\n";
    std::cout << "5. Разблокировать счёт\n";
    std::cout << "6. Показать баланс\n";
    std::cout << "7. Показать статус (активен/заблокирован)\n";
    std::cout << "8. Показать лимиты (min/max)\n";
    std::cout << "9. Показать договор\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    std::string name;
    std::cout << "Введите имя владельца счёта: ";
    std::getline(std::cin, name);

    double min_sum, max_sum, initial_balance;
    std::cout << "Введите минимальный баланс (min_sum): ";
    std::cin >> min_sum;
    std::cout << "Введите максимальный баланс (max_sum, 0 = бесконечность): ";
    std::cin >> max_sum;
    if (max_sum == 0) max_sum = INFINITY;
    std::cout << "Введите начальный баланс: ";
    std::cin >> initial_balance;
    clearInput();

    account acc(name, "Standart diablo Gringo Dogovor", initial_balance, min_sum, max_sum);

    int choice;
    do {
        printMenu();
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1: {
                double sum;
                std::cout << "Сумма пополнения: ";
                std::cin >> sum;
                clearInput();
                if (acc.AddMoney(sum))
                    std::cout << "Операция успешна. Новый баланс: " << acc.getBalance() << std::endl;
                else
                    std::cout << "Ошибка пополнения!" << std::endl;
                break;
            }
            case 2: {
                double sum;
                std::cout << "Сумма снятия: ";
                std::cin >> sum;
                clearInput();
                if (acc.giveMoney(sum))
                    std::cout << "Операция успешна. Новый баланс: " << acc.getBalance() << std::endl;
                else
                    std::cout << "Ошибка снятия!" << std::endl;
                break;
            }
            case 3: {
                std::string reason;
                std::cout << "Причина блокировки: ";
                std::getline(std::cin, reason);
                if (acc.BlockAcc(reason))
                    std::cout << "Счёт заблокирован (причина: " << reason << ")" << std::endl;
                else
                    std::cout << "Не удалось заблокировать счёт (возможно, пустая причина без 666)!" << std::endl;
                break;
            }
            case 4: {
                // блокировка без причины – сработает только если balance == min_sum+666
                if (acc.BlockAcc(""))
                    std::cout << "Счёт заблокирован навсегда (666)!" << std::endl;
                else
                    std::cout << "Блокировка без причины не выполнена – баланс не равен min_sum+666." << std::endl;
                break;
            }
            case 5:
                if (acc.UnlockAcc())
                    std::cout << "Счёт разблокирован." << std::endl;
                else
                    std::cout << "Не удалось разблокировать (вечная блокировка)." << std::endl;
                break;
            case 6:
                std::cout << "Текущий баланс: " << acc.getBalance() << std::endl;
                break;
            case 7:
                if (acc.IsActive())
                    std::cout << "Счёт активен." << std::endl;
                else
                    std::cout << "Счёт заблокирован." << std::endl;
                break;
            case 8:
                std::cout << "Минимальный баланс: " << acc.getMinSum() << std::endl;
                std::cout << "Максимальный баланс: " << acc.getMaxSum() << std::endl;
                break;
            case 9:
                std::cout << "Договор: " << acc.getDogovor() << std::endl;
                break;
            case 0:
                std::cout << "До свидания!" << std::endl;
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова." << std::endl;
        }
    } while (choice != 0);

    return 0;
}