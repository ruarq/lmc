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

#include <functional>
#include <string>

/**
 * @brief Namespace for the command line option parser lmc uses.
 */
namespace Lm::Opt
{

using OptionInvokeFn = std::function<void(std::string)>;

/**
 * @brief Describes a command line option.
 */
class Option final
{
public:
	/**
	 * @brief Used to determine the kind of argument the option takes
	 */
	enum class Argument
	{
		None,		 /// The option accepts no argument
		Optional,	 /// The option optionally accepts an argument
		Required	 /// The option requires an argument
	};

	/**
	 * @brief Used to determine the kind of an option string.
	 */
	enum class Type
	{
		None,
		ShortOption,
		LongOption
	};

	/**
	 * @brief Parse a string to get the type of an option.
	 * @param string The string to parse.
	 * @return Lm::Opt::Option::Type::None if it's not an option
	 */
	static auto GetType(const std::string &string) -> Type;

public:
	/**
	 * @brief Initialize a Option object
	 * @param longString The long version of the option.
	 * @param shortString The short version of the option.
	 * @param type The type of the option.
	 */
	Option(const std::string &longString,
		const char shortString,
		const Argument argument,
		const OptionInvokeFn &Invoke);

public:
	/// The long version of the option.
	/// Leave empty if the option doesn't have a long version.
	const std::string longString;

	/// The short version of the option.
	/// Leave empty if the option doesn't have a short version.
	const char shortString;

	/// The type of the option. See Lm::Opt::Option::Argument for more details.
	const Argument argument;

	/// The invokation function. Get's called by Lm::Opt::Parse,
	/// if the option occured in argv
	const std::function<void(std::string)> Invoke;
};

}
