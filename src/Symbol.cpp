/**
 * @author ruarq
 * @date 16.02.2022 
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

#include "Symbol.hpp"

namespace Lm
{

std::vector<std::string> Symbol::pool;
std::unordered_map<std::string, symbol_id_t> Symbol::stringToId;

auto Symbol::NextId() -> symbol_id_t
{
	static symbol_id_t nextId = 0;
	return nextId++;
}

auto Symbol::DropHashmap() -> void
{
	stringToId.clear();
}

Symbol::Symbol(std::string &&str)
{
	operator=(std::move(str));
}

auto Symbol::String() const -> const std::string &
{
	return pool[id];
}

auto Symbol::operator=(std::string &&str) -> Symbol &
{
	if (stringToId.find(str) == stringToId.end())
	{
		id = NextId();
		stringToId[str] = id;
		pool.push_back(std::move(str));
	}
	else
	{
		id = stringToId.at(str);
	}

	return *this;
}

Symbol::operator bool() const
{
	return id != invalidId;
}

}
