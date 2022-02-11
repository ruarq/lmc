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

#include "Locale.hpp"

namespace Lm::Locale
{

auto Country() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(3, 2);
}

auto Language() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(0, 2);
}

auto Encoding() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(lang.find_last_of('.') + 1);
}

}
