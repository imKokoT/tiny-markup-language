#pragma once
#include"config.hpp"

enum class TokenType {

};

struct Token {
    int64 line, col;
    TokenType type;
    wchar* value;

    Token(TokenType token, int64 line, int64 col);
    Token(TokenType token, int64 line, int64 col, wchar* value);
    ~Token();
};
