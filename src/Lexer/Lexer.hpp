/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#pragma once

#include <string>
#include <vector>

#include <fmt/format.h>

#include "../File.hpp"
#include "Token.hpp"

namespace Lm
{

class Lexer final
{
public:
	/**
	 * @brief Run the lexer over a source
	 */
	auto Run(const File &file) -> std::vector<Token>;

private:
	/**
	 * @brief Lex the next token
	 */
	auto NextToken() -> Token;

	/**
	 * @brief Lex an identifier
	 */
	auto Identifier() -> Token;

	/**
	 * @brief Lex a number literal
	 */
	auto Number() -> Token;

	/**
	 * @brief Lex a string literal
	 */
	auto String() -> Token;

	/**
	 * @brief Skip whitespace
	 */
	auto SkipWhitespace() -> void;

	/**
	 * @brief Get the current char
	 */
	auto Current() const -> char;

	/**
	 * @brief Consume the current char
	 */
	auto Consume() -> char;

	/**
	 * @brief Match the string against all characters at current + following
	 * @return True if the string matches
	 */
	auto Match(const std::string &match, const size_t offset = 0) -> bool;

	/**
	 * @return True if eof, false if not
	 */
	auto Eof() const -> bool;

private:
	const File *file;
	FileLoc pos;
	size_t current;
};

}
