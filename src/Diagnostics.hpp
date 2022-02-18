/**
 * @author ruarq
 * @date 18.02.2022 
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

#include <fmt/color.h>
#include <fmt/format.h>

#include "File.hpp"
#include "Lexer/Token.hpp"
#include "Localization/Locale.hpp"

namespace Lm
{

/**
 * @brief Used to present diagnostic information to the user
 * includes
 * - warnings
 * - errors
 */
class Diagnostics final
{
public:
	/**
	 * @brief Initialize a diagnostics object for a file
	 */
	Diagnostics(const File &file);

public:
	/**
	 * @brief Emit a error message
	 */
	auto Error(const SourcePos &where, const std::string &what) const -> void;

private:
	/**
	 * @brief Load a line in from the file buffer
	 */
	auto LoadLine(const SourcePos &pos) const -> std::string;

private:
	const File &file;
};

}
