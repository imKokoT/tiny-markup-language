#include <tml/data.hpp>

template <typename T, typename>
inline bool tml::TMLObject::Is()
{
    return this != nullptr ? typeid(*this) == typeid(T) : false;
}
