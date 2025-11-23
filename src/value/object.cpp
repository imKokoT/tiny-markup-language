#include<tml/value.hpp>
#include<stdexcept>


namespace tml
{

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool isValidKey(const std::string& key) {
    if (key.empty() || !isLetter(key[0]))
        return false;

    for (char c : key.substr(1))
        if (!isLetter(c) && !isDigit(c) && c != '_')
            return false;
    
    return true;
}

Object::Object(std::initializer_list<containerT::value_type> init) {
    for (auto p : init) {
        if (!isValidKey(p.first))
            throw std::invalid_argument("Variable name '" + p.first + "' can contain ASCII English symbols (`a-z` and `A-Z`), numbers (`0-9`) and `-`, `_`, `.` symbols. Variable starts only from alphabet symbols.");

        _values[p.first] = p.second;
    }
}

Value &Object::At(const std::string& key) { 
    if (!isValidKey(key))
        throw std::invalid_argument("Variable name'" + key + "'can contain ASCII English symbols (`a-z` and `A-Z`), numbers (`0-9`) and `-`, `_`, `.` symbols. Variable starts only from alphabet symbols.");
    return _values.at(key); 
}


} // namespace tml
