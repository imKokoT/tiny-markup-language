#pragma once
#include"config.hpp"
#include<string_view>


struct Token {
    enum Type {
        End,        // EOF
        EOL,        // semi or \n
        
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
        String
    };

    size_t line, col;
    Type type;
    std::string_view value;

    Token(Type token, size_t line, size_t col);
    Token(Type token, size_t line, size_t col, std::string_view value);
};
