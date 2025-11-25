#include "token.hpp"
#include <string_view>


Token::Token(Type token, size_t line_, size_t col_) 
    : type(token),
      line(line_),
      col(col_) {}


Token::Token(Type token, size_t line_, size_t col_, std::string_view value_)
    : type(token),
      line(line_),
      col(col_),
      value(value_) {}
