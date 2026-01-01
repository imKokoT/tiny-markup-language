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

/// @brief returns true if c is `␣;:,\\n\\t` 
inline bool isEndlOrSpace(char c) {
    return (c == ' ' || c == ';' || c == ':' || c == ',' || c == '\n' || c == '\t');
}

/// @brief returns true if c is `;\n` 
inline bool isEnd(char c) {
    return (c == ';' || c == '\n');
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
//  HELPER READERS
////////////////////////////////////////////////////////////

/// @brief reads whitespace until EOL 
/// @returns true if found not EOL symbol 
bool Lexer::readUntilEnd() {
    const char* start = cursor;
    const char* delta = cursor;
    size_t len = 0;


    while (delta < end && *delta != '\n'){
        char c = *delta;

        if (!(c == ' ' || c == '\t')){
            col += len;
            cursor = delta;
            return true;
        }

        len++; delta++;
    }

    cursor = delta+1;
    col = 1;
    line++;
    return false;
}

void Lexer::pushIndentation()
{
    const char* start = cursor;
    const char* delta = cursor;
    size_t len = 0;
    char iSymbol = *cursor;
    
    while (delta < end) {
        char c = *delta;
        if ((iSymbol == ' ' && c == '\t') || (iSymbol == '\t' && c == ' '))
            error("mix of indentation symbols is not allowed");
        else if (c == '\n') { // whitespace lines
            delta++; line++; col = 1;
            cursor = delta;
retry:
            if (readUntilEnd()){
                len = cursor - delta;
                delta = cursor;
                col = 1;
                break;
            }
            delta = cursor;
            goto retry;
        }
        else if (c != ' ' && c != '\t')
            break;

        delta++; len++;
    }

    auto& last = indentStack.back();
    if (last.first > 0 && last.second != iSymbol)
        error("child's indentation symbol must be same as parent's");
    else if (last.first >= (int)len)
        error("child's indentation length must be bigger than parent's");
    
    indentStack.push_back(std::pair(len, iSymbol));
    cursor = delta;
    col += len;
}

void Lexer::readIndentation(Token::Type dedentToken) {
    const char* start = cursor;
    const char* delta = cursor;
    size_t len = 0;
    char iSymbol = *cursor;

    while (delta < end) {
        char c = *delta;
        if ((iSymbol == ' ' && c == '\t') || (iSymbol == '\t' && c == ' '))
            error("mix of indentation symbols is not allowed");
        else if (c == '\n') // whitespace line
            goto skip;
        else if (c != ' ' && c != '\t')
            break;

        delta++; len++;
    }

    auto& last = indentStack.back();
    if (last.first > 0 && len != 0 && last.second != iSymbol)
        error("indentation symbol must be same as at last line");
    else if (last.first > (int)len) { // dedent
        int i = indentStack.size();
        do {
            indentStack.pop_back();
            emit(dedentToken);
            last = indentStack.back();

            if (last.first < int(len))
                error("invalid indentation length");

            i--;
        } while (last.first < int(len) && i > 1);
    }
    else if (last.first > (int)len)
        error("invalid indentation length");

skip:
    cursor = delta;
    col += len;
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
    const char* start = cursor;
    const char* delta = cursor;
    size_t len = 0;

    delta++;
    while (delta < end) {
        char c = *delta;
        if (c == '\n')
            error("string must be closed");
        else if (c == quote && *(delta-1) != '\\')
            break;
        len++; delta++;
    }

    emit(Token::String, std::string_view(start+1, len));
    cursor = delta+1;
    col += len+1;
}

void Lexer::readUnQuotedString() {
    const char* start = cursor;
    const char* delta = cursor;
    size_t len = 0;
    size_t whitespace = 0; 

    while (!isEnd(*delta) && delta < end) {
        char c = *delta;
        
        whitespace++;
        if (!(c == ' ' || c == '\t'))
            whitespace = 0;

        delta++; len++;
    }

    emit(Token::String, std::string_view(start, len-whitespace));
    col += len;
    cursor = delta;
}

void Lexer::readMultilineString(char quote) {
    const char* start = cursor;
    const char* delta = cursor;
    const char* pieceStart = nullptr; // TODO: evil stuff
    size_t deltaIndent = 1;
    char iSymbol = *cursor;

    while(cursor < end) {
        char c = *delta;
        if (c == quote && *(delta-1) != '\\')
            break;
        else if (deltaIndent < col && ((iSymbol == ' ' && c == '\t') || (iSymbol == '\t' && c == ' ')))
            error("mix of indentation symbols is not allowed");
        else if (deltaIndent < col && c != iSymbol)
            error("wrong multiline string indentation");
        else if (col == deltaIndent)
            pieceStart = delta;
        else if (c == '\n') {
            deltaIndent = 0;
            line++;
            emit(Token::StringPiece, std::string_view(pieceStart, delta - pieceStart));
        }
        deltaIndent++; delta++;
    }

    col = deltaIndent;
    cursor = delta + 1;
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
                readIndentation(Token::RBrace);
                break;

            case '{':
                error("not implemented");
                break;
            case '[':
                error("not implemented");
                break;
            case ':': { // read indented object
                emit(Token::Eq);
                emit(Token::LBrace);
                col++; cursor++;
                if (readUntilEnd()) 
                    error("unexpected symbol '" + std::to_string(*cursor) + "'");
                pushIndentation();
            } break;

            case '=':
                emit(Token::Eq);
                col++; cursor++;
                break;

            case '"':
            case '\'': {
                const char* start = cursor;
                size_t dcol = col;

                // TODO: may optimize later...
                cursor++; col++;
                if (readUntilEnd()){
                    col = dcol; cursor = start;    
                    readQuotedString(c);
                }
                else {
                    col = dcol;
                    readMultilineString(c);
                }
            } break;
            default:
                if (isLetter(c) && tokens.back().type != Token::Eq) 
                    readIdentifierOrConst();
                else if (isNumStart(c, next)) 
                    readNumber();
                else 
                    readUnQuotedString();
        }
    }
}


////////////////////////////////////////////////////////////
//  ENTRY
////////////////////////////////////////////////////////////

const std::vector<Token>& Lexer::lex()
{
    indentStack.push_back({-1, ' '}); // push root indentation

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
            case '\'': {
                const char* start = cursor;
                size_t dcol = col;

                // TODO: may optimize later...
                cursor++; col++;
                if (readUntilEnd()){
                    col = dcol; cursor = start;    
                    readQuotedString(c);
                }
                else {
                    col = dcol;
                    readMultilineString(c);
                }
            } break;
            default:
                if (isLetter(c)){
                    readIdentifierOrConst();
                    if (tokens.back().type == Token::Identifier) {
                        // pop it due simplifying reading indented object
                        cursor -= col - tokens.back().col;
                        tokens.pop_back();
                        
                        emit(Token::LBrace);
                        pushIndentation();
                        readIndentedObject();
                        emit(Token::RBrace);
                    }
                } 
                else if (isNumStart(c, next)) readNumber();
                else readUnQuotedString();
        }
    }

    emit(Token::End); // EOF
    return tokens;
}
