#pragma once
#include"../token.hpp"
#include<vector>
#include<string_view>
#include<string>


class Lexer {
    const char* cursor;
    const char* end;
    size_t line = 1, col = 1;
    std::vector<Token> tokens;

    std::vector<std::pair<int, char>> indentStack;

    void emit(Token::Type type);
    void emit(Token::Type type, std::string_view value);

    void readIndentedObject();
    void readBracedObject();
    void readList();
    void readIdentifierOrConst();
    void readQuotedString(char quote);
    void readUnQuotedString();
    void readNumber();

    void error(std::string msg);
public:
    Lexer(std::string_view src) : cursor(src.data()), end(cursor + src.size()) {}

    const std::vector<Token>& lex();
};
