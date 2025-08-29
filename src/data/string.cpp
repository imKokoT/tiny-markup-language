#include<tml/data.hpp>
#include<string>


namespace tml {

String::String(const String &other)
{
    _size = other._size;
    _data = new wchar_t[_size+1];
    for (size_t i=0; i < _size; ++i)
        _data[i] = other._data[i];
    _data[_size] = '\0';
}
String::String(const char *other, const size_t size)
{
    _size = size;
    _data = new wchar_t[_size];
    for (size_t i=0; i < _size; ++i)
        _data[i] = other[i];
}
String::String(const wchar_t *other, const size_t size)
{
    _size = size;
    _data = new wchar_t[_size];
    for (size_t i=0; i < _size; ++i)
        _data[i] = other[i];
}
String::String(const std::string &other)
{
    _size = other.size();
    _data = new wchar_t[_size+1];
    for (size_t i=0; i < _size; ++i)
        _data[i] = other[i];
    _data[_size] = '\0';
}
String::String(const std::wstring &other)
{
    _size = other.size();
    _data = new wchar_t[_size+1];
    for (size_t i=0; i < _size; ++i)
        _data[i] = other[i];
    _data[_size] = '\0';
}
    
wchar_t* String::GetData() const
{
    return _data;
}

size_t String::Length() const 
{ 
    return _size; 
}

std::string String::GetString() const
{
    std::string result;
    result.reserve(wcslen(_data));

    for (size_t i = 0; i<_size; ++i)
        result.push_back(static_cast<char>(_data[i])); // lossy cast
    
    return result;
}

std::wstring String::GetWString() const
{
    return std::wstring(_data);
}

wchar_t String::operator[](const size_t index) const 
{
    return _data[index];
}

String &String::operator=(const std::wstring &other)
{
    delete[] _data;
    _size = other.size();
    _data = new wchar_t[_size+1];

    for (size_t i=0; i < _size; ++i)
        _data[i] = other[i];
    _data[_size] = '\0';

    return *this;
}
String &String::operator=(const std::string &other)
{
    delete[] _data;
    _size = other.size();
    _data = new wchar_t[_size+1];
    
    for (size_t i=0; i < _size; ++i)
        _data[i] = other[i];
    _data[_size] = '\0';

    return *this;
}
String &String::operator=(const wchar_t *other)
{
    delete[] _data;
    _size = std::wcslen(other);
    _data = new wchar_t[_size+1];

    for (size_t i = 0; i <= _size; ++i)
        _data[i] = other[i];

    return *this;
}
String &String::operator=(const char *other)
{
    delete[] _data;
    _size = std::strlen(other);
    _data = new wchar_t[_size+1];

    for (size_t i = 0; i <= _size; ++i)
        _data[i] = other[i];

    return *this;
}
String &String::operator=(const String &other)
{
    delete[] _data;
    _size = other._size;
    _data = new wchar_t[_size+1];
    
    for (size_t i=0; i < _size; ++i)
        _data[i] = other._data[i];
    _data[_size] = '\0';

    return *this;
}

tml::String::~String()
{
    delete[] _data;
}

} // namespace tml
