#include"lexer.hpp"
#include"../token.hpp"
#include<tml/errors.hpp>
#include <iostream>
#include <string>


////////////////////////////////////////////////////////////
//  HELPER FUNCTIONS
////////////////////////////////////////////////////////////

/// @brief returns true if `c` is `0-9` 
inline bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

/// @brief returns true if `c` is `a-zA-Z`
inline bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/// @brief returns `true` if given char is numeric format; if `sign` is digit, retuns `true`
inline bool isNumStart(char sign, char next) {
    return (isDigit(sign) ||
            ( // -0 +0 -. +.  
                (sign == '-' || sign == '+') && (next == '.' || isDigit(next))
            ) ||
            ( // .0
                sign == '.' && isDigit(next)
            )
        );
}

/// @brief returns true if c is `␣;\\n\\t` 
inline bool isEndlOrSpace(char c){
    return (c == ' ' || c == ';' || c == '\n' || c == '\t');
}


////////////////////////////////////////////////////////////
//  OTHER LEXER METHODS
////////////////////////////////////////////////////////////

void Lexer::emit(Token::Type type) {
    tokens.push_back(Token(type, line, col));
}
void Lexer::emit(Token::Type type, std::string_view value) {
    tokens.push_back(Token(type, line, col, value));
}

void Lexer::error(std::string msg) {
    throw tml::LoadError("syntax error at [" + std::to_string(line) + "," + std::to_string(col) + "]: " + msg);
}


////////////////////////////////////////////////////////////
//  READ DATA TYPES
////////////////////////////////////////////////////////////

void Lexer::readIdentifierOrConst() {
    error("not implemented");
}

void Lexer::readQuotedString(char quote) {
    error("not implemented");
}

void Lexer::readUnQuotedString()
{
    error("not implemented");
}

void Lexer::readNumber() {
    const char* start = cursor;
    const char* delta = cursor;
    bool eFound = false;
    bool isFloat = *start == '.'; // first can be `.`
    
    // skip first checked char
    delta++;
    size_t len = 1;

    if (*delta == 'e' || *delta == 'E')
        readUnQuotedString(); // fall to string

    while (!isEndlOrSpace(*delta) && delta < end) {
        if (*delta == '.')
            if(isFloat)
                readUnQuotedString(); // fall to string
            else
                isFloat = true;

        else if (*delta == 'e' || *delta == 'E')
            if (eFound)
                readUnQuotedString(); // fall to string
            else
                eFound = isFloat = true;

        else if (!isDigit(*delta))
            readUnQuotedString(); // fall to string

        delta++; len++;
    }

    if (isFloat)
        emit(Token::Float, std::string_view(start, len));
    else
        emit(Token::Integer, std::string_view(start, len));
    col += len;
    cursor = delta;
}

////////////////////////////////////////////////////////////
//  ENTRY
////////////////////////////////////////////////////////////
const std::vector<Token>& Lexer::lex()
{
    while (cursor < end) {
        char c = *cursor;
        char next = *(cursor + 1);

        switch (c) {
            case ' ':
            case '\t':
            case ';':
                col++; cursor++;
                break;
            case '\n':
                cursor++;
                col = 1; line++;
                break;

            case '"':
            case '\'':
                readQuotedString(c);
                break;
            default:
                if (isNumStart(c, next)) readNumber(); 
                else readUnQuotedString();
        }
    }

    emit(Token::End); // EOF
    return tokens;
}
