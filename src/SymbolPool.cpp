/**
 * @author ruarq
 * @date 15.02.2022 
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

#include "SymbolPool.hpp"

#include <list>

namespace Lm
{

SymbolPool::ContainerType SymbolPool::pool;

auto symbol_id_t_hasher::operator()(const symbol_id_t id) -> size_t
{
	return id;
}

auto fast_string_hash::operator()(const std::string &string) -> size_t
{
}

Symbol::Symbol(const symbol_id_t id)
	: id(id)
{
}

auto Symbol::String() const -> const std::string &
{
	return SymbolPool::At(*this);
}

auto operator==(const Symbol &l, const Symbol &r) -> bool
{
	if (l.id == r.id)
	{
		return l.String() == r.String();
	}

	return false;
}

auto SymbolPool::Insert(std::string &&str) -> Symbol
{
	const auto hash = Hash<std::hash<std::string>>(str);
	pool[hash] = str;
	return Symbol(hash);
}

auto SymbolPool::At(const Symbol &symbol) -> const std::string &
{
	return pool.at(symbol.id);
}

}
