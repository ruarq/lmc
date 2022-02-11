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

	if (string.size() >= 2 && string.substr(0, 2) == "--"s)
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
