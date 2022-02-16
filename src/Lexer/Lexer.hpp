/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * 
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
#include "../Localization/Locale.hpp"
#include "../Logger.hpp"
#include "Token.hpp"

namespace Lm
{

class Lexer final
{
public:
	/**
	 * @brief Run the lexer over a source
	 */
	auto Run(const std::string &filename, std::string &&source) -> std::vector<Token>;

	/**
	 * @return True if the lexer had an error, false if not
	 */
	auto HadError() const -> bool;

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
	 * @return True if whitespace was skipped
	 */
	auto SkipWhitespace() -> bool;

	/**
	 * @brief Skip comments
	 * @return True if a comment was skipped
	 */
	auto SkipComments() -> bool;

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

	/**
	 * @brief Call if the lexer encounters something unexpected
	 */
	template<typename... Args>
	auto Error(const File::Pos &where, const size_t offset, const fmt::format_string<Args...> &fmt, Args &&...args)
		-> void
	{
		hadError = true;
		Logger::ErrorFile(name, where, fmt, args...);

		// TODO(ruarq): Improve this section if possible
		const auto color = fmt::color::yellow_green;

		const auto lineStart = source.rfind('\n', offset) + 1;
		const auto lineEnd = source.find('\n', lineStart + 1);
		const std::string line = source.substr(lineStart, lineEnd - lineStart);

		fmt::print("{}\n", line);
		for (size_t i = 0; i < where.column; ++i)
		{
			if (line[i] != '\t')
			{
				fmt::print(" ");
			}
			else
			{
				fmt::print("\t");
			}
		}
		fmt::print(fg(color), "^\n");
	}

private:
	std::string name;
	std::string source;

	File::Pos pos;
	size_t current;

	bool hadError = false;
};

}
