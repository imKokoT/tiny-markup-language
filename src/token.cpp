#include "token.hpp"

Token::Token(TokenType token, int64 line, int64 col) {
    type = token;
    line = line;
    col = col;
}

Token::Token(TokenType token, int64 line, int64 col, const wchar *value) {
    type = token;
    line = line;
    col = col;
    value = value;
}

Token::~Token() {
    if (value != nullptr)
        delete[] value;
}
