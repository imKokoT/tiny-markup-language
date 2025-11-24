#pragma once
#include<tml/config.hpp>
#include<exception>
#include<string>


namespace tml {

class TML_API LoadError : public std::exception {
    std::string msg;
public:
    LoadError(const std::string& m) : msg(m) {}
    LoadError(const char* m) : msg(m) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

} // namespace tml
