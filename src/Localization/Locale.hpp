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

#pragma once

#include <array>
#include <fstream>
#include <string>
#include <unordered_map>

#include <fmt/format.h>

#include "../Env.hpp"

namespace Lm
{

class Locale final
{
public:
	/**
	 * @brief Get the full locale
	 */
	static auto Full() -> std::string;

	/**
	 * @brief Get the country
	 */
	static auto Country() -> std::string;

	/**
	 * @brief Get the language
	 */
	static auto Language() -> std::string;

	/**
	 * @brief Get the encoding
	 */
	static auto Encoding() -> std::string;

	/**
	 * @brief Get the default locale
	 */
	static auto Default() -> std::string;

	/**
	 * @brief Load the locale from a file
	 * @return Whether loading was successful or not
	 */
	static auto LoadFromFile(const std::string &filename) -> bool;

	/**
	 * @brief Get a phrase from the locale
	 */
	static auto Get(const std::string &phrase) -> const std::string &;

private:
	static std::unordered_map<std::string, std::string> phrases;
};

}
