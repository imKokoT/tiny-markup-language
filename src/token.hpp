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

    int64 line, col;
    Type type;
    std::string_view value;

    Token(Type token, int64 line, int64 col);
    Token(Type token, int64 line, int64 col, std::string_view value);
};
