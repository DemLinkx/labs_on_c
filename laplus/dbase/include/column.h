#ifndef COLUMN_H
#define COLUMN_H

#include "base_column.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <type_traits>

template <typename T>
class Column : public BaseColumn {
public:
    Column(std::string name) : BaseColumn(std::move(name)) {}

    size_t size() const override { return data_.size(); }
    
    std::string get_value_str(size_t index) const override {
        if (index >= data_.size()) return "NULL";
        std::ostringstream oss;
        oss << data_[index];
        return oss.str();
    }

    T& operator[](size_t index) { return data_.at(index); }
    const T& operator[](size_t index) const { return data_.at(index); }
    void push_back(const T& val) { data_.push_back(val); }

    double get_mean() const {
        if (!std::is_arithmetic<T>::value) {
            throw std::runtime_error("get_mean() requires numeric column type");
        }
        if (data_.empty()) return 0.0;
        double sum = 0.0;
        for (const auto& v : data_) {
            sum += static_cast<double>(v);
        }
        return sum / static_cast<double>(data_.size());
    }

    double get_median() const {
        if (!std::is_arithmetic<T>::value) {
            throw std::runtime_error("get_median() requires numeric column type");
        }
        if (data_.empty()) return 0.0;
        std::vector<T> sorted = data_;
        std::sort(sorted.begin(), sorted.end());
        size_t mid = sorted.size() / 2;
        if (sorted.size() % 2 == 0) {
            return (static_cast<double>(sorted[mid-1]) + static_cast<double>(sorted[mid])) / 2.0;
        }
        return static_cast<double>(sorted[mid]);
    }

    double get_std_dev() const {
        if (!std::is_arithmetic<T>::value) {
            throw std::runtime_error("get_std_dev() requires numeric column type");
        }
        if (data_.size() < 2) return 0.0;
        double mean = get_mean();
        double sq_sum = 0.0;
        for (const auto& v : data_) {
            double diff = static_cast<double>(v) - mean;
            sq_sum += diff * diff;
        }
        return std::sqrt(sq_sum / static_cast<double>(data_.size()));
    }

    std::pair<T, size_t> get_mode(size_t n = 1) const {
        if (data_.empty()) {
            throw std::runtime_error("Column is empty, cannot compute mode");
        }
        std::map<T, size_t> freq;
        for (const auto& v : data_) {
            freq[v]++;
        }
        
        std::vector<std::pair<T, size_t>> sorted(freq.begin(), freq.end());
        std::sort(sorted.begin(), sorted.end(), 
            [](const std::pair<T, size_t>& a, const std::pair<T, size_t>& b) {
                return a.second > b.second;
            });
        
        if (n < 1 || n > sorted.size()) {
            throw std::out_of_range("Mode index out of range");
        }
        return sorted[n - 1];
    }

private:
    std::vector<T> data_;
};

#endif