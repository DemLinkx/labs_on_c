#ifndef DATABASE_H
#define DATABASE_H

#include "table.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

class DataBase {
public:
    DataBase(std::string name);
    
    Table& create_table(std::string table_name);
    Table* get_table(std::string name);
    
    void print_structure() const;
    void print_all() const;

private:
    std::string name_;
    std::unordered_map<std::string, std::unique_ptr<Table>> tables_;
};

#endif