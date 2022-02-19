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
	LM_DEBUG("{} {} {}", where.line, where.column, where.offset);
	const auto line = LoadLine(where);
	fmt::print("{} {} {}\n{}\n",
		fmt::format(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "{}:", Locale::Get("ERROR")),
		fmt::format(fmt::emphasis::bold, "{}:{}:{}:", file.Name(), where.line, where.column),
		what,
		line);

	Here(line, where.column - 1, where.column - 1, '^', '~');
}

auto Diagnostics::LoadLine(const SourcePos &pos) const -> std::string
{
	auto start = file.Buf() + pos.offset - 1;
	auto end = start + 1;

	// find the start of the line
	while (*start != '\n' && start >= file.Buf())
	{
		--start;
	}
	++start;

	// find the end of the line
	while (*end != '\n' && end < file.Buf() + file.Size())
	{
		++end;
	}

	return std::string(start, end);
}

auto Diagnostics::Here(const std::string &line,
	const column_t from,
	const column_t to,
	const char pointer,
	const char underline) const -> void
{
	std::string pre;
	for (column_t i = 0; i < from; ++i)
	{
		if (line[i] == '\t')
		{
			pre += "\t";
		}
		else
		{
			pre += underline;
		}
	}

	std::string post;
	for (column_t i = from; i < to; ++i)
	{
		if (line[i] == '\t')
		{
			post += "\t";
		}
		else
		{
			post += underline;
		}
	}

	fmt::print(fmt::fg(fmt::color::green_yellow), "{}{}{}\n", pre, pointer, post);
}

}
