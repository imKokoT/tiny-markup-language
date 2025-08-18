#pragma once
#include"config.hpp"

enum class TokenType {
    End,        // semi or \n
    Identifier,
    Eq,         // =
    Colon,      // :
    Coma,       // ,
    
    LBrace, RBrace,     // { }
    LBracket, RBracket, // [ ]
    LQuote, RQuote,     // quotes
    
    Null,
    True, False,
    Integer,
    Float,
    StringBody
};

struct Token {
    int64 line, col;
    TokenType type;
    wchar* value;

    Token(TokenType token, int64 line, int64 col);
    Token(TokenType token, int64 line, int64 col, const wchar* value);
    ~Token();
};
