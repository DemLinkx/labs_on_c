#include "include/database.h"
#include <iostream>
#include <iomanip>

int main() { // демонстрация работы
    try {
        DataBase db("SchoolDB");
        
        auto& students = db.create_table("students");
        students.add_column<int>("id");
        students.add_column<std::string>("name");
        students.add_column<double>("grade");
        students.add_column<std::string>("group");
        
        auto& subjects = db.create_table("subjects");
        subjects.add_column<int>("code");
        subjects.add_column<std::string>("title");
        auto* id_col = dynamic_cast<Column<int>*>(students.get_column("id"));
        auto* name_col = dynamic_cast<Column<std::string>*>(students.get_column("name"));
        auto* grade_col = dynamic_cast<Column<double>*>(students.get_column("grade"));
        auto* group_col = dynamic_cast<Column<std::string>*>(students.get_column("group"));
        
        // Добавляем данные
        id_col->push_back(1);
        name_col->push_back("Alice");
        grade_col->push_back(4.8);
        group_col->push_back("CS-101");
        
        id_col->push_back(2);
        name_col->push_back("Bob");
        grade_col->push_back(3.9);
        group_col->push_back("CS-101");
        
        id_col->push_back(3);
        name_col->push_back("Charlie");
        grade_col->push_back(4.5);
        group_col->push_back("CS-102");
        
        id_col->push_back(4);
        name_col->push_back("Diana");
        grade_col->push_back(4.8);
        group_col->push_back("CS-102");
        
        id_col->push_back(5);
        name_col->push_back("Eve");
        grade_col->push_back(3.9);
        group_col->push_back("CS-101");
        
        db.print_structure();
        
        db.print_all();
        
        std::cout << "\n=== Analytics ===\n";
        if (grade_col) {
            std::cout << "Grade mean: " << std::fixed << std::setprecision(2) 
                      << grade_col->get_mean() << "\n";
            std::cout << "Grade median: " << grade_col->get_median() << "\n";
            std::cout << "Grade std dev: " << grade_col->get_std_dev() << "\n";
        }
        
        if (group_col) {
            auto mode = group_col->get_mode(1);
            std::cout << "Most popular group: " << mode.first 
                      << " (" << mode.second << " students)\n";
        }
        
        std::cout << "\nBefore: grade[0] = " << (*grade_col)[0] << "\n";
        (*grade_col)[0] = 5.0;
        std::cout << "After:  grade[0] = " << (*grade_col)[0] << "\n";
        
        std::cout << "\nSuccess!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}