/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
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
