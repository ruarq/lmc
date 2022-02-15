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

#pragma once

#include <string>
#include <unordered_map>

namespace Lm
{

using symbol_id_t = unsigned long;

struct symbol_id_t_hasher final
{
	auto operator()(const symbol_id_t id) -> size_t;
};

struct fast_string_hash final
{
	auto operator()(const std::string &string) -> size_t;
};

template<typename Hasher>
auto Hash(const std::string &str) -> symbol_id_t
{
	return Hasher()(str);
}

class Symbol final
{
public:
	explicit Symbol(const symbol_id_t id);

public:
	/**
	 * @brief Get string value of the symbol
	 */
	auto String() const -> const std::string &;

public:
	const symbol_id_t id;
};

auto operator==(const Symbol &l, const Symbol &r) -> bool;

/**
 * @brief I honestly believe this implementation is 100% dumb and there is a smart way to do it.
 */
class SymbolPool final
{
public:
	using ContainerType = std::unordered_map<symbol_id_t, std::string>;

public:
	/**
	 * @brief Insert a new object into the string
	 * @return A instance of symbol representing that string
	 */
	static auto Insert(std::string &&str) -> Symbol;

	/**
	 * 
	 */
	static auto At(const Symbol &symbol) -> const std::string &;

private:
	static ContainerType pool;
};

}
