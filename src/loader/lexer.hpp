#pragma once
#include"../token.hpp"
#include<vector>
#include<string_view>


class Lexer {
    const char* cursor;
    const char* end;
    size_t line = 1, col = 1;
    std::vector<Token> tokens;

    void emit(Token::Type type);
    void emit(Token::Type type, std::string_view value);
public:
    Lexer(std::string_view src) : cursor(src.data()), end(cursor + src.size()) {}

    const std::vector<Token>& lex();
};
