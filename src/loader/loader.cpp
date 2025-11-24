#include"lexer.hpp"
#include<tml/loader.hpp>
#include<string_view>

namespace tml
{
        
Value loads(std::string_view data)
{
    Lexer lexer(data);
    lexer.lex();

    return Value();
}

} // namespace tml