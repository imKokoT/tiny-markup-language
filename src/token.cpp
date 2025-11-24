#include "token.hpp"
#include <string_view>


Token::Token(Type token, int64 line_, int64 col_) 
    : type(token),
      line(line_),
      col(col_) {}


Token::Token(Type token, int64 line_, int64 col_, std::string_view value_)
    : type(token),
      line(line_),
      col(col_),
      value(value_) {}
