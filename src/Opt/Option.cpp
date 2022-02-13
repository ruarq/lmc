/**
 * @author ruarq
 * @date 11.02.2022 
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

#include "Option.hpp"

using namespace std::string_literals;

namespace Lm::Opt
{

auto Option::GetType(const std::string &string) -> Option::Type
{
	if (string.empty())
	{
		return Type::None;
	}

	if (string.substr(0, 2) == "--"s)
	{
		return Type::LongOption;
	}
	else if (string.substr(0, 1) == "-"s)
	{
		return Type::ShortOption;
	}

	return Type::None;
}

Option::Option(const std::string &longString,
	const char shortString,
	const Argument argument,
	const OptionInvokeFn &Invoke,
	const std::string &description)
	: longString(longString)
	, shortString(shortString)
	, argument(argument)
	, Invoke(Invoke)
	, description(description)
{
}

}
