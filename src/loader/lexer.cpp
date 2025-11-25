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
    const char* start = cursor;
    const char* delta = cursor;
    size_t len = 0;

    while (!isEndlOrSpace(*delta) && delta < end) {
        if (!(*delta == '.' || *delta == '_' || *delta == '-' || isLetter(*delta) || isDigit(*delta))){
            readUnQuotedString(); // fall to string
            return;
        }
        delta++; len++;
    }

    // check for constants
    std::string_view i(start, len);
    if (i == "T" || i == "true")
        emit(Token::True);
    else if (i == "F" || i == "false")
        emit(Token::False);
    else if (i == "null")
        emit(Token::Null);
    // is identifier
    else
        emit(Token::Identifier, i);
    col += len;
    cursor = delta;
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
    size_t len = 1;
    bool eFound = false;
    bool isFloat = *start == '.'; // first can be `.`
    
    // skip first checked char
    delta++;

    if (*delta == 'e' || *delta == 'E') {
        readUnQuotedString(); // fall to string
        return;
    }

    while (!isEndlOrSpace(*delta) && delta < end) {
        if (*delta == '.')
            if(isFloat) {
                readUnQuotedString(); // fall to string
                return;
            }
            else
                isFloat = true;

        else if (*delta == 'e' || *delta == 'E')
            if (eFound) {
                readUnQuotedString(); // fall to string
                return;
            }
            else
                eFound = isFloat = true;

        else if (!isDigit(*delta)){
            readUnQuotedString(); // fall to string
            return;
        }

        delta++; len++;
    }

    if (isFloat)
        emit(Token::Float, std::string_view(start, len));
    else
        emit(Token::Integer, std::string_view(start, len));
    col += len;
    cursor = delta;
}


void Lexer::readIndentedObject() {
    while (cursor < end) {
        char c = *cursor;
        char next = *(cursor + 1);

        switch (c) {
            case ' ':
            case '\t':
                col++; cursor++;
                break;
            case ';':
                emit(Token::EOL);
                col++; cursor++;
                break;
            case '\n':
                emit(Token::EOL);
                col = 1; line++; cursor++;
                break;

            case '{':
                error("not implemented");
                break;
            case '[':
                error("not implemented");
                break;
            case ':':
                error("not implemented");
                break;
            case '=':
                emit(Token::Eq);
                col++; cursor++;
                break;

            case '"':
            case '\'':
                readQuotedString(c);
                break;
            default:
                if (isLetter(c) && tokens.back().type != Token::Eq) 
                    readIdentifierOrConst();
                else if (isNumStart(c, next)) 
                    readNumber();
                else 
                    readUnQuotedString();
        }
    }

    emit(Token::RBrace);
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
            // whitespaces
            case ' ':
            case '\t':
            case ';':
                col++; cursor++;
                break;
            case '\n':
                cursor++;
                col = 1; line++;
                break;

            case '{':
                error("not implemented");
                break;
            case '[':
                error("not implemented");
                break;

            case '"':
            case '\'':
                readQuotedString(c);
                break;
            default:
                if (isLetter(c)){
                    readIdentifierOrConst();
                    if (tokens.back().type == Token::Identifier){
                        Token i = std::move(tokens.back());
                        tokens.back() = Token(Token::LBrace, line, col);
                        tokens.push_back(std::move(i));
                        readIndentedObject();
                    }
                } 
                else if (isNumStart(c, next)) readNumber();
                else readUnQuotedString();
        }
    }

    emit(Token::End); // EOF
    return tokens;
}
