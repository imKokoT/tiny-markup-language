#pragma once
#include"config.hpp"
#include <type_traits>

namespace tml
{

class Bool;
class Number;
class String;
class List;
class Object;

template<typename T>
struct IsTMLObj : std::disjunction<
    std::is_same<T, Bool>,
    std::is_same<T, Number>,
    std::is_same<T, String>,
    std::is_same<T, List>, 
    std::is_same<T, Object>> {};    

/// @brief Abstract tml object
class TML_API TMLObject {
public:
    /// @brief return true if this TMLObject is T
    template<typename T, typename = std::enable_if_t<IsTMLObj<T>::value>>
    bool Is();
};

class TML_API Number : TMLObject {    
public:
    enum class ValueType : uint8_t { Integer, Float };

    Number(const Number& other);
    
    template<typename T>
    Number(T value);
    template<> Number(int64_t);
    template<> Number(int32_t);
    template<> Number(float);
    template<> Number(double);

    template<typename T>
    T GetValue() const;
    
    template<typename T>
    void SetValue(T value);

    bool IsInteger() const;
    bool IsFloat() const;

    Number& operator=(const Number& other);
    template<typename T>
    Number& operator=(const T& other);
private:
    union {
        int64_t i;
        double d;
    } _value;
    ValueType _type;
};

template int64_t TML_API Number::GetValue<int64_t>() const;
template int32_t TML_API Number::GetValue<int32_t>() const;
template float   TML_API Number::GetValue<float>() const;
template double  TML_API Number::GetValue<double>() const;
template void TML_API Number::SetValue(int64_t);
template void TML_API Number::SetValue(int32_t);
template void TML_API Number::SetValue(float);
template void TML_API Number::SetValue(double);
template TML_API Number& Number::operator=(const int64_t&);
template TML_API Number& Number::operator=(const int32_t&);
template TML_API Number& Number::operator=(const float&);
template TML_API Number& Number::operator=(const double&);
    
} // namespace tml
