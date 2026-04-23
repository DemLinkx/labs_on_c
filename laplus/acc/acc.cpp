#include "acc.hpp"

account::account(str name, str dogovor, double balance, double min_sum, double max_sum) {
    this->is_active = true;
    this->name = name;
    this->dogovor = dogovor;
    this->min_sum = min_sum;
    this->max_sum = max_sum;
    this->balance = 0.0;
    this->is_official_prichina_blokirovki = false;
    this->prichina_blokirovki = "";
    this->taboo = "Action!!! \nBalance value equal to minimum value + 666 is not allowed"
                  "If detected, your account will be completely blocked and the money will become the"
                  "property of the bank.\n"
                  "\t(c) Dmitri C++ \nGrinGGots Bank (r)\n";

    std::cout << this->taboo << std::endl;
    if ((balance >= min_sum) && (balance <= max_sum)) {
        this->balance = balance;
    }
    if (balance > max_sum) {
        std::cout << "Bro you are really rich i.t.d, but we don`t give open this bank account. \n"
                     "Reread politics about users."
                     "We sorry"
                     "\t(c) Dmitri C++ \nGrinGGots Bank (r)" << std::endl;
    }
}

double account::getBalance() const {
    return this->balance;
}

double account::getMaxSum() const {
    return this->max_sum;
}

double account::getMinSum() const {
    return this->min_sum;
}

str account::getDogovor() const {
    return this->dogovor;
}

bool account::IsActive() const {
    return this->is_active;
}

bool account::AddMoney(double sum) {
    if ((this->max_sum >= this->balance + sum) && (sum > 0) && (!this->is_official_prichina_blokirovki)) {
        this->balance += sum;
        if ((this->balance - this->min_sum - 666) < 1) {
            this->prichina_blokirovki = "666 OMG";
            this->is_official_prichina_blokirovki = true;
            this->is_active = false;
            std::cout << this->taboo << "YOU BLOCKED FOREVER:)" << std::endl;
        }
        return true;
    } else if ((this->max_sum >= this->balance + sum) && (sum > 0) && (this->is_official_prichina_blokirovki)) {
        std::cout << this->taboo << "YOU BLOCKED FOREVER :)" << std::endl;
        return false;
    } else
        return false;
}

bool account::giveMoney(double sum) {
    if ((this->min_sum > this->balance - sum) && (sum > 0)) {
        std::cout << "We sorry, but you too much penniless for this summ. Don`t worry :)" << std::endl;
        return false;
    }
    if ((this->min_sum <= this->balance - sum) && (sum > 0) && (this->is_active)) {
        this->balance -= sum;
        if ((this->balance - this->min_sum - 666) < 1) {
            this->prichina_blokirovki = "666 OMG";
            this->is_official_prichina_blokirovki = true;
            this->is_active = false;
            std::cout << this->taboo << "YOU BLOCKED FOREVER :)" << std::endl;
        }
        return true;
    } else if ((this->min_sum <= this->balance - sum) && (sum > 0) && (!this->is_active)) {
        if (this->is_official_prichina_blokirovki) {
            std::cout << this->taboo << "YOU BLOCKED FOREVER :)" << std::endl;
        } else {
            std::cout << "YOU BLOCKED NOT FOREVER WE ARE SORT OUT SITUATION :| " << std::endl;
        }
        return false;
    }
    return false;
}

bool account::BlockAcc(str prichina) {
    std::cout << prichina << std::endl;
    if (prichina == "") {
        if ((this->balance - this->min_sum - 666) < 1) {
            this->prichina_blokirovki = "666 OMG";
            this->is_official_prichina_blokirovki = true;
            this->is_active = false;
            return true;
        } else {
            return false;
        }
    } else {
        this->is_official_prichina_blokirovki = false;
        this->prichina_blokirovki = prichina;
        this->is_active = false;
        return true;
    }
}

bool account::UnlockAcc() {
    if (!this->is_official_prichina_blokirovki) {
        this->is_active = true;
        std::cout << "We sorry\n";
        return true;
    } else {
        std::cout << this->taboo << "YOU BLOCKED FOREVER :)" << std::endl;
        return false;
    }
}