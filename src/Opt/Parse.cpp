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

#include "Parse.hpp"

#include <iostream>

using namespace std::string_literals;

namespace Lm::Opt
{

auto Parse(const std::vector<std::string> &argv, const std::vector<Option> &options)
	-> std::vector<std::string>
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

auto ParseOption(const std::vector<std::string> &argv,
	size_t &arg,
	const std::vector<Option> &options) -> bool
{
	bool optionNotFound = true;
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
					optionNotFound = false;
					InvokeOption(argv, arg, option);
					break;
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
					optionNotFound = false;
					InvokeOption(argv, arg, option);
					break;
				}
			}
		}
		break;

		default: return false;
	}

	if (optionNotFound)
	{
		// TODO(ruarq): Quickly write a logging library as we do not want to use std::cout raw
		std::cout << argv.at(0) << ": unrecognized command-line option '" << argv.at(arg) << "'\n";
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

auto GenerateHelpText(const std::vector<Option> &options) -> std::string
{
	std::string helpText;

	for (const auto &option : options)
	{
		helpText += "\t";

		if (option.shortString && option.longString.empty())
		{
			helpText += "-"s + option.shortString;
		}
		else if (!option.shortString && !option.longString.empty())
		{
			helpText += "--"s + option.longString;
		}
		else if (option.shortString && !option.longString.empty())
		{
			helpText += "-"s + option.shortString;
			helpText += ", --"s + option.longString;
		}

		if (!option.description.empty())
		{
			helpText += "\n\t\t";
			helpText += option.description;
			helpText += "\n";
		}

		helpText += "\n";
	}

	return helpText.substr(0, helpText.find_last_not_of('\n') + 2);
}

}
