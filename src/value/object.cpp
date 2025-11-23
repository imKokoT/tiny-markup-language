#include<tml/value.hpp>
#include<stdexcept>


namespace tml
{
using containerT = std::map<std::string, Value>;
using iterator = containerT::iterator;
using const_iterator = containerT::const_iterator;

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool Object::isValidKey(const std::string& key) {
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
const Value &Object::At(const std::string &key) const
{
    return _values.at(key);
}

void Object::Insert(const std::string &key, const Value &value)
{
    if (!isValidKey(key))
        throw std::invalid_argument("Variable name'" + key + "'can contain ASCII English symbols (`a-z` and `A-Z`), numbers (`0-9`) and `-`, `_`, `.` symbols. Variable starts only from alphabet symbols.");
    _values[key] = value;
}

bool Object::IsEmpty() const { return _values.empty(); }
size_t Object::Length() const { return _values.size(); }
void Object::Erase(const std::string &key) { _values.erase(key); }
void Object::Clear() { _values.clear(); }

iterator Object::Find(const std::string &key) { return _values.find(key); }
const_iterator Object::Find(const std::string &key) const { return _values.find(key); }
bool Object::Contains(const std::string &key) const { return _values.find(key) != _values.end(); }

iterator Object::begin() { return _values.begin(); } 
iterator Object::end() { return _values.end(); } 
const_iterator Object::begin() const { return _values.begin(); } 
const_iterator Object::end() const { return _values.end(); } 
const_iterator Object::cbegin() const { return _values.cbegin(); } 
const_iterator Object::cend() const { return _values.cend(); }

Value &Object::operator[](const std::string &key) { return At(key); }
const Value &Object::operator[](const std::string &key) const { return At(key); }

} // namespace tml
