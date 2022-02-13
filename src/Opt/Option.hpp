/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
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

public:
	/**
	 * @brief Parse a string to get the type of an option.
	 * @param string The string to parse.
	 * @return Lm::Opt::Option::Type::None if it's not an option
	 */
	static auto GetType(const std::string &string) -> Type;

public:
	static constexpr auto noShortOption = 0;
	static constexpr auto noLongOption = "";

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
		const OptionInvokeFn &Invoke,
		const std::string &description = {});

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

	/// The description of the Option. This is optional, but helpful
	/// if you want to use Lm::Opt::GenerateHelpText, which uses
	/// the description of the Option to generate a help text
	const std::string description;
};

}
