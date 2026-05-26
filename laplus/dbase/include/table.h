#ifndef TABLE_H
#define TABLE_H

#include "base_column.h"
#include "column.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>

class Table {
public:
    Table(std::string name);
    
    std::string get_name() const { return name_; }
    template<typename T>
    void add_column(std::string col_name);
    
    BaseColumn* get_column(size_t index);
    BaseColumn* get_column(std::string name);
    size_t column_count() const;
    size_t row_count() const;
    
    void print() const;
    void print_structure() const;

private:
    std::string name_;
    std::vector<std::unique_ptr<BaseColumn>> columns_;
    static void print_row(const std::string& cell);
};

template<typename T>
void Table::add_column(std::string col_name) {
    columns_.push_back(std::make_unique<Column<T>>(std::move(col_name)));
}

#endif