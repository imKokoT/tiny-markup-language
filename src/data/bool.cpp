#include<tml/data.hpp>

namespace tml {

Bool::Bool(const Bool&other) : _value(other._value) {}
Bool::Bool(bool value) : _value(value) {}

bool Bool::GetValue() const { return _value; }
void Bool::SetValue(bool value) { _value = value; }

Bool& Bool::operator=(const Bool& other) 
{
    _value = other._value;
    return *this;
}
Bool& Bool::operator=(const bool& other) {
    _value = other;
    return *this;
}

} // namespace tml
