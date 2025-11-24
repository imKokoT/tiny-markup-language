#include"lexer.hpp"
#include"../token.hpp"


void Lexer::emit(Token::Type type) {
    tokens.push_back(Token(type, line, col));
}
void Lexer::emit(Token::Type type, std::string_view value) {
    tokens.push_back(Token(type, line, col, value));
}


const std::vector<Token>& Lexer::lex()
{
    emit(Token::Type::Identifier, std::string_view(cursor, 1));
    emit(Token::Type::End);

    return tokens;
}
