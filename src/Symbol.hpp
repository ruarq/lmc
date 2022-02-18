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

#pragma once

#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "Hashes/MurmurHash.hpp"

namespace Lm
{

using symbol_id_t = unsigned long;

class Symbol final
{
public:
	static constexpr auto invalidId = std::numeric_limits<symbol_id_t>::max();

public:
	static auto NextId() -> symbol_id_t;

	/**
	 * @brief Frees the memory of the stringToId hashmap. We don't need it anymore after lexing.
	 */
	static auto DropHashmap() -> void;

public:
	static std::vector<std::string> pool;
	static std::unordered_map<std::string, symbol_id_t, MurmurHash> stringToId;

public:
	Symbol() = default;
	Symbol(std::string &&str);

public:
	auto String() const -> const std::string &;

public:
	auto operator=(std::string &&str) -> Symbol &;
	operator bool() const;

private:
	symbol_id_t id = invalidId;
};

}
