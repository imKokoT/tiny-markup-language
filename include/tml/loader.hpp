#pragma once
#include"config.hpp"
#include"model.hpp"
#include<string_view>


namespace tml
{

Value TML_API loads(std::string_view data);    

} // namespace tml
