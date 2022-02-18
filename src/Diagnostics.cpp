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

#include "Diagnostics.hpp"

namespace Lm
{

Diagnostics::Diagnostics(const File &file)
	: file(file)
{
}

auto Diagnostics::Error(const SourcePos &where, const std::string &what) const -> void
{
	const auto line = LoadLine(where);
	fmt::print("{} {} {}\n{}\n",
		fmt::format(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "{}:", Locale::Get("ERROR")),
		fmt::format(fmt::emphasis::bold, "{}:{}:{}:", file.Name(), where.line, where.column),
		what,
		line);

	std::string pointer;
	for (column_t i = 0; i < where.column - 1; ++i)
	{
		if (line[i] == '\t')
		{
			pointer += "\t";
		}
		else
		{
			pointer += "~";
		}
	}
	fmt::print(fmt::fg(fmt::color::green_yellow), "{}^\n", pointer);
}

auto Diagnostics::LoadLine(const SourcePos &pos) const -> std::string
{
	auto start = file.Buf() + pos.offset;
	auto end = start;

	// find the start of the line
	while (*start != '\n')
	{
		--start;
	}
	++start;

	// find the end of the line
	while (*end != '\n')
	{
		++end;
	}

	return std::string(start, end);
}

}
