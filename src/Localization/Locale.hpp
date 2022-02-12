/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * lmc is the official compiler for the Lumin programming language.
 * Copyright (C) 2022 ruarq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <array>
#include <fstream>
#include <string>
#include <unordered_map>

#include <fmt/format.h>

#include "../Env.hpp"
#include "../Log/Debug.hpp"

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

public:
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
