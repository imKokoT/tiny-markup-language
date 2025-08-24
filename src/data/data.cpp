#include <tml/data.hpp>
#include <typeinfo>

template <typename T, typename>
inline bool tml::TMLObject::Is() const
{
    return this != nullptr ? typeid(*this) == typeid(T) : false;
}
