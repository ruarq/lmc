/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#include "Token.hpp"

namespace Lm
{

Token::Token(const Type type, const std::string &literal, const FileLoc &start, const FileLoc &end)
	: type(type)
	, literal(literal)
	, start(start)
	, end(end)
{
}

}
