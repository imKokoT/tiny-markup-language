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
        Number(int64_t value);
        Number(double value);

        template<typename T>
        T GetValue() const {
            if constexpr (std::is_same_v<T, int64_t>) {
                if (_type != ValueType::Integer)
                    return static_cast<int64_t>(_value.d);
                return _value.i;
            } 
            else if constexpr (std::is_same_v<T, double>) {
                if (_type == ValueType::Integer) 
                    return static_cast<double>(_value.i);
                return _value.d;
            }
            else {
                static_assert(!sizeof(T), "Unsupported type!");
            }
        }
        
        template<typename T>
        void SetValue(T value) const;

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

} // namespace tml
