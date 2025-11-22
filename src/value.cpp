#include<tml/value.hpp>

namespace tml {

Value::Value()                      : _data(std::monostate{}) {}
Value::Value(std::nullptr_t)        : _data(std::monostate{}) {}
Value::Value(bool v)                : _data(v) {}
Value::Value(int v)                 : _data(int64_t(v)) {}
Value::Value(int64_t v)             : _data(v) {}
Value::Value(float v)               : _data(double(v)) {}
Value::Value(double v)              : _data(v) {}
Value::Value(const char * v)        : _data(std::string(v)) {}
Value::Value(const std::string & v) : _data(v) {}
Value::Value(std::string && v)      : _data(std::move(v)) {}
Value::Value(const List& v)         : _data(v) {}
Value::Value(List&& v)              : _data(std::move(v)) {}

} // namespace tml
