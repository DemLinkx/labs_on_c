#ifndef BASE_COLUMN_H
#define BASE_COLUMN_H

#include <string>
#include <cstddef>

class BaseColumn {
public:
    BaseColumn(std::string name);
    virtual ~BaseColumn() = default;
    
    std::string get_name() const;
    virtual size_t size() const = 0;
    virtual std::string get_value_str(size_t index) const = 0;

protected:
    std::string name_;
};

#endif