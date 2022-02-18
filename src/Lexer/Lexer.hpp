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

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "../Diagnostics.hpp"
#include "../File.hpp"
#include "../Logger.hpp"
#include "../Macros.hpp"
#include "Token.hpp"

namespace Lm
{

class Lexer final
{
public:
	Lexer(const File &file, const Diagnostics &diagnostics);

public:
	/**
	 * @brief Get the next token
	 */
	auto NextToken() -> Token;

	/**
	 * @return True if eof
	 */
	auto Eof() const -> bool;

private:
	/**
	 * @brief Lex one token
	 */
	auto LexToken() -> Token;

	/**
	 * @brief Next char
	 */
	inline auto Next() -> void;

private:
	const char *start;
	const char *curr;
	const char *end;

	SourcePos pos;
	line_t line;
	column_t column;

	Diagnostics diagnostics;

#if LM_LEXER_BUFFER_ENABLE
	size_t bufToken = LM_LEXER_BUFFER_SIZE;
	std::array<Token, LM_LEXER_BUFFER_SIZE> buffer;
#endif
};

}
