#include<tml/data.hpp>
#include<stdexcept>

tml::Number::Number(const Number& other)
{
    _value = other._value;
    _type = other._type;
}
tml::Number::Number(int64_t value) : _type(ValueType::Integer) { _value.i = value; }
tml::Number::Number(double value) : _type(ValueType::Float) {_value.d = value; }

// template <typename T>
// T tml::Number::GetValue() const
// {
//     if constexpr (std::is_same_v<T, int64_t>) {
//         if (_type != ValueType::Integer)
//             throw std::runtime_error("Not an integer");
//         return _value.i;
//     } 
//     else if constexpr (std::is_same_v<T, double>) {
//         if (_type == ValueType::Integer) 
//             return static_cast<double>(_value.i);
//         return _value.d;
//     } 
//     else {
//         static_assert(!sizeof(T), "Unsupported type!");
//     }
// }

template <typename T>
void tml::Number::SetValue(T value) const
{
    if constexpr (std::is_same_v<T, int64_t>) {
        _value.i = value;
        _type = ValueType::Integer;
    }
    else if constexpr (std::is_same_v<T, double>) {
        _value.d = value;
        _type = ValueType::Float;
    }
    else {
        static_assert(!sizeof(T), "Unsupported type!");
    }
}

bool tml::Number::IsInteger() const { return _type == ValueType::Integer; }
bool tml::Number::IsFloat() const { return _type == ValueType::Float; }

tml::Number& tml::Number::operator=(const Number& other)
{
    _value = other._value;
    _type = other._type;
    return *this;
}

template <typename T>
tml::Number& tml::Number::operator=(const T &other)
{
    if constexpr (std::is_same_v<T, int64_t>) {
        _value.i = other;
        _type = ValueType::Integer;
    }
    else if constexpr (std::is_same_v<T, double>) {
        _value.d = other;
        _type = ValueType::Float;
    }
    else {
        static_assert(!sizeof(T), "Unsupported type!");
    }
}

// template int64_t tml::Number::GetValue<int64_t>() const;
// template double  tml::Number::GetValue<double>() const;
