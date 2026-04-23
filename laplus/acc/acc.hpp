#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <string>
#include <cmath>

typedef std::string str;

class account {
public:
    // Конструктор с параметрами по умолчанию
    account(str name, 
            str dogovor = "Standart diablo Gringo Dogovor",
            double balance = 0.0,
            double min_sum = 0.0,
            double max_sum = INFINITY);

    double getBalance() const;
    double getMaxSum() const;
    double getMinSum() const;
    str getDogovor() const;          // добавлено определение
    bool IsActive() const;
    bool AddMoney(double sum);
    bool giveMoney(double sum);
    bool BlockAcc(str prichina);
    bool UnlockAcc();

private:
    str name;
    str dogovor;
    double balance;
    double min_sum;
    double max_sum;
    bool is_active;
    bool is_official_prichina_blokirovki;
    str prichina_blokirovki;
    str taboo;
};

#endif