#include "../include/table.h"

Table::Table(std::string name) : name_(std::move(name)) {}

BaseColumn* Table::get_column(size_t index) {
    if (index < columns_.size()) {
        return columns_[index].get();
    }
    return nullptr;
}

BaseColumn* Table::get_column(std::string name) {
    for (auto& col : columns_) {
        if (col->get_name() == name) {
            return col.get();
        }
    }
    return nullptr;
}

size_t Table::column_count() const {
    return columns_.size();
}

size_t Table::row_count() const {
    if (columns_.empty()) {
        return 0;
    }
    return columns_[0]->size();
}

void Table::print_row(const std::string& cell) {
    std::string out = cell;
    if (out.length() > 12) {
        out = out.substr(0, 9) + "...";
    }
    std::cout << " " << std::left << std::setw(14) << out << " |";
}

void Table::print() const {
    std::cout << "\n+--------------------------------------------------------+\n";
    std::cout << "| TABLE: " << std::left << std::setw(48) << name_ << " |\n";
    std::cout << "+--------------------------------------------------------+\n";
    std::cout << " |";
    for (auto& col : columns_) {
        print_row(col->get_name());
    }
    std::cout << "\n +--------------+--------------+--------------+--------------+\n";
    
    size_t rows = row_count();
    for (size_t r = 0; r < rows; ++r) {
        std::cout << " |";
        for (auto& col : columns_) {
            print_row(col->get_value_str(r));
        }
        std::cout << "\n";
    }
    std::cout << " +--------------+--------------+--------------+--------------+\n";
    std::cout << " Rows: " << rows << " | Cols: " << columns_.size() << "\n";
}

void Table::print_structure() const {
    std::cout << "Table: " << name_ << "\n";
    for (auto& col : columns_) {
        std::cout << "  - " << col->get_name() << " (" << col->size() << " rows)\n";
    }
}