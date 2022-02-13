/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
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

	if (string.substr(0, 2) == "--"s)
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
