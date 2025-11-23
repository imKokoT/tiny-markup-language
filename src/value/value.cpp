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
Value::Value(const Object& v)       : _data(v) {}
Value::Value(Object&& v)            : _data(std::move(v)) {}

bool Value::isNull() const { return std::holds_alternative<std::monostate>(_data); }
bool Value::isBool() const { return std::holds_alternative<bool>(_data); }
bool Value::isNumber() const { return std::holds_alternative<int64_t>(_data) || std::holds_alternative<double>(_data); }
bool Value::isString() const { return std::holds_alternative<std::string>(_data); }
bool Value::isList() const { return std::holds_alternative<List>(_data); }
bool Value::isObject() const { return std::holds_alternative<Object>(_data); }

bool &tml::Value::asBool() { return std::get<bool>(_data); }
const bool &tml::Value::asBool() const { return std::get<bool>(_data); }

int64_t &tml::Value::asInt() { return std::get<int64_t>(_data); }
const int64_t &tml::Value::asInt() const { return std::get<int64_t>(_data); }

double &tml::Value::asDouble() { return std::get<double>(_data); }
const double &tml::Value::asDouble() const { return std::get<double>(_data); }

std::string &tml::Value::asString() { return std::get<std::string>(_data); }
const std::string &tml::Value::asString() const { return std::get<std::string>(_data); }

List &tml::Value::asList() { return std::get<List>(_data); }
const List &tml::Value::asList() const { return std::get<List>(_data); }

Object &tml::Value::asObject() { return std::get<Object>(_data); }
const Object &tml::Value::asObject() const { return std::get<Object>(_data); }

} // namespace tml

