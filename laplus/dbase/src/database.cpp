#include "../include/database.h"

DataBase::DataBase(std::string name) : name_(std::move(name)) {}

Table& DataBase::create_table(std::string table_name) {
    if (tables_.find(table_name) != tables_.end()) {
        throw std::runtime_error("Table '" + table_name + "' already exists");
    }
    auto tbl = std::make_unique<Table>(std::move(table_name));
    Table* ptr = tbl.get();
    tables_[ptr->get_name()] = std::move(tbl);
    return *ptr;
}

Table* DataBase::get_table(std::string name) {
    auto it = tables_.find(name);
    if (it != tables_.end()) {
        return it->second.get();
    }
    return nullptr;
}

void DataBase::print_structure() const {
    std::cout << "\nDatabase: " << name_ << " (" << tables_.size() << " tables)\n";
    for (const auto& pair : tables_) {
        pair.second->print_structure();
    }
}

void DataBase::print_all() const {
    std::cout << "\n============================================================\n";
    std::cout << " DATABASE: " << name_ << "\n";
    std::cout << "============================================================\n";
    for (const auto& pair : tables_) {
        pair.second->print();
    }
}