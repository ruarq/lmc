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

#include "Parse.hpp"

#include <iostream>

using namespace std::string_literals;

namespace Lm::Opt
{

auto Parse(const std::vector<std::string> &argv, const std::vector<Option> &options) -> std::vector<std::string>
{
	std::vector<std::string> nonOptions;

	for (size_t arg = 1; arg < argv.size(); ++arg)
	{
		if (!ParseOption(argv, arg, options))
		{
			nonOptions.push_back(argv.at(arg));
		}
	}

	return nonOptions;
}

auto ParseOption(const std::vector<std::string> &argv, size_t &arg, const std::vector<Option> &options) -> bool
{
	const std::string argString = argv.at(arg);
	switch (Option::GetType(argString))
	{
		case Option::Type::ShortOption:
		{
			const auto &argName = argString.at(1);
			for (const auto &option : options)
			{
				if (option.shortString == argName)
				{
					InvokeOption(argv, arg, option);
				}
			}
		}
		break;

		case Option::Type::LongOption:
		{
			const auto &argName = argString.substr(2);
			for (const auto &option : options)
			{
				if (option.longString == argName)
				{
					InvokeOption(argv, arg, option);
				}
			}
		}
		break;

		default: return false;
	}

	return true;
}

auto InvokeOption(const std::vector<std::string> &argv, size_t &arg, const Option &option) -> void
{
	switch (option.argument)
	{
		case Option::Argument::Required:
		{
			try
			{
				const std::string &argument = argv.at(++arg);
				option.Invoke(argument);
			}
			catch (std::exception &e)
			{
				// TODO(ruarq): Nice error output
				std::cout << e.what() << "\n";
			}
		}
		break;

		case Option::Argument::Optional:
		{
			if (arg + 1 >= argv.size())
			{
				option.Invoke("");
				break;
			}

			const std::string &argument = argv.at(++arg);
			const Option::Type argumentType = Option::GetType(argument);
			if (argumentType != Option::Type::None)
			{
				option.Invoke("");
			}
			else
			{
				option.Invoke(argument);
			}
		}
		break;

		default:
		case Option::Argument::None: option.Invoke(""); break;
	}
}

}
