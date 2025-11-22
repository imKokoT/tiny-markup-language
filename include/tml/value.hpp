#pragma once
#include"config.hpp"
#include<variant>
#include<string>
#include<map>
#include<vector>

namespace tml 
{
class Value;


class TML_API Object {
public:
    using containerT = std::map<std::string, Value>;
    using iterator = containerT::iterator;
    using const_iterator = containerT::const_iterator;
private:
    containerT _values;
public:
    Object() = default;
    Object(std::initializer_list<std::pair<std::string, Value>>);

    Value& At(const std::string& key);
    const Value& At(const std::string& key) const;
    bool IsEmpty() const;
    size_t Length() const;
    void Insert(const std::string& key, const Value& value);
    void Erase(const std::string& key); 
    
    iterator Find(const std::string& key);
    const_iterator Find(const std::string& key) const;
    bool Contains(const std::string& key) const;
    
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    
    Value& operator[](const std::string& key);
    const Value& operator[](const std::string& key) const;
};


class TML_API List {
public:
    using containerT = std::vector<Value>;
    using iterator = containerT::iterator;
    using const_iterator = containerT::const_iterator;
private:
    containerT _values;
public:
    List() = default;
    List(std::initializer_list<Value>);

    Value& At(size_t index);
    const Value& At(size_t index) const;
    void PushBack(const Value& v);
    void PushBack(Value&& v);
    void Clear();
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    size_t Length() const;
    bool IsEmpty() const;

    Value& operator[](size_t index);
    const Value& operator[](size_t index) const;
};


class TML_API Value {
    enum class Type { Null, Bool, Number, String, List, Object };

    std::variant<
        std::monostate,
        bool,
        int64_t, 
        double,
        std::string,
        List,
        Object
    > _data;

public:
    Value(); // Null
    Value(std::nullptr_t);
    Value(bool);
    Value(int);
    Value(int64_t);
    Value(float);
    Value(double);
    Value(const char*);
    Value(const std::string&);
    Value(std::string&&);
    Value(const List&);
    Value(List&&);
    Value(const Object&);
    Value(Object&&);
};

}; // namespace tml
