#include<tml/model.hpp>
#include<initializer_list>
#include<stdexcept>


namespace tml
{
using containerT = std::vector<Value>;
using iterator = containerT::iterator;
using const_iterator = containerT::const_iterator;


List::List(std::initializer_list<Value> init) : _values(init) {}

Value& List::At(size_t index)
{
    if (index >= _values.size()) 
        throw std::out_of_range("tml::List::At");
    return _values[index];
}
const Value &List::At(size_t index) const
{
    if (index >= _values.size()) 
        throw std::out_of_range("tml::List::At");
    return _values[index];
}

void List::PushBack(const Value &v) { _values.push_back(v); }
void List::PushBack(Value &&v) { _values.push_back(std::move(v)); }

void List::Clear() { _values.clear(); }

iterator List::begin() { return _values.begin(); }
iterator List::end() { return _values.end(); }
const_iterator List::begin() const { return _values.begin(); }
const_iterator List::end() const { return _values.end(); }

size_t List::Length() const { return _values.size(); }
bool List::IsEmpty() const { return _values.empty(); }

Value &List::operator[](size_t index) { return At(index); }
const Value &List::operator[](size_t index) const { return At(index); }

} // namespace tml

