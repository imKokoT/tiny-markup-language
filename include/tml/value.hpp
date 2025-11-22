#pragma once
#include"config.hpp"
#include<variant>
#include<string>
#include<vector>
#include<map>


namespace tml {

class TML_API Value {
    enum class Type { Null, Bool, Number, String, List, Object };

    std::variant<
        std::monostate,
        bool,
        int64_t, 
        double,
        std::string,
        // std::vector<Value>,
        // std::map<std::string, Value>
    > _data;

public:
    Value(); // Null
    Value(bool);
    Value(int);
    Value(uint32_t);
    Value(int64_t);
    Value(uint64_t);
    Value(float);
    Value(double);
    Value(const char*);
    Value(const std::string&);
    Value(std::string&&);
    // Value(std::initializer_list<Value>);
    // Value(std::initializer_list<std::pair<std::string, Value>>);
};

}; // namespace tml
