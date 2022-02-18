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

#include <chrono>
#include <string>
#include <vector>

#include <fmt/chrono.h>
#include <fmt/format.h>

#include "Diagnostics.hpp"
#include "File.hpp"
#include "Lexer/Lexer.hpp"
#include "Localization/Locale.hpp"
#include "Logger.hpp"
#include "Macros.hpp"
#include "Opt/Parse.hpp"
#include "Parser/Parser.hpp"

using namespace std::string_literals;

auto LoadLocale() -> void
{
	auto locale = Lm::Locale::Full();
	if (locale.empty())
	{
		locale = Lm::Locale::Default();
	}
	Lm::Locale::LoadFromFile("data/locales/"s + locale);
}

// TODO(ruarq): File a bug report about this, clang format formats
// "auto main(int argc, char **argv) -> int"
// to
// "automain(int argc, char **argv) -> int"
// auto main(int argc, char **argv) -> int
int main(int argc, char **argv)
{
	LoadLocale();

	// We need the help text in the "help" option, but
	// we can only generate it after declaring the option
	// array.
	std::string helpText;

	// Whether benchmarking should be done or not
	bool benchmark = false;

	const std::vector<Lm::Opt::Option> options = {
	// clang-format off
		{
			"version",
			'v',
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				fmt::print("Version");
				std::exit(0);
			},
			Lm::Locale::Get("HELP_VERSION_DESCRIPTION")
		},
		{
			"locale",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				fmt::print("{}\n", Lm::Locale::Full());
				std::exit(0);
			},
			Lm::Locale::Get("HELP_LOCALE_DESCRIPTION")
		},
		{
			"benchmark",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[&benchmark](const std::string &) {
				benchmark = true;
			},
			Lm::Locale::Get("HELP_BENCHMARK_DESCRIPTION")
		},
		{
			"help",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[&helpText, &argv](const std::string &) {
				fmt::print(Lm::Locale::Get("USAGE_STRING") + "\n"s, argv[0]);
				fmt::print("{}:\n", Lm::Locale::Get("OPTIONS"));
				fmt::print("{}\n", helpText);
				std::exit(0);
			},
			Lm::Locale::Get("HELP_HELP_DESCRIPTION")
		}
	// clang-format on
	};

	// Generate help text
	helpText = Lm::Opt::GenerateHelpText(options);

	// Remove duplicates
	auto RemoveDups = [](auto &list) {
		const auto copy = std::move(list);

		for (auto &elem : copy)
		{
			bool insert = true;
			for (auto &item : list)
			{
				if (item == elem)
				{
					insert = false;
					break;
				}
			}

			if (insert)
			{
				list.push_back(std::move(elem));
			}
		}
	};

	auto filenames = Lm::Opt::Parse(std::vector<std::string>(argv, argv + argc), options);
	RemoveDups(filenames);

	LM_DEBUG("Discovering {} file(s)...", filenames.size());

	for (const auto &filename : filenames)
	{
		Lm::File file(filename);

		if (!file.Buf())
		{
			// TODO(ruarq): Make fatal error out of this
			Lm::Logger::Error(Lm::Locale::Get("FATAL_NO_SUCH_FILE_OR_DIRECTORY"), filename);
			return 1;
		}

		/**
		 * Lexing
		 */
		Lm::Diagnostics diagnostics(file);
		Lm::Lexer lexer(file, diagnostics);
		Lm::Parser parser(lexer, diagnostics);
		Lm::Ast::TranslationUnit *unit = nullptr;

		if (benchmark)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			{
				unit = parser.Run();
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto duration = std::chrono::duration<double>(end - start);

			Lm::Logger::Info("{}: - {} - {:.2f} MiB/s",
				file.Name(),
				duration,
				(double)(file.Size()) / (duration.count() * (double)(1 << 20)));
		}
		else
		{
			unit = parser.Run();
		}

		Lm::Symbol::DropHashmap();

		delete unit;

		// for (const auto &token : tokens)
		// {
		// 	fmt::print("'{}' - {}\n",
		// 		token.symbol ? token.symbol.String() : "No symbol",
		// 		content.substr(token.offset, token.size));
		// }

		/**
		 * Parsing
		 */
		// Lm::Parser parser;
		// auto translationUnit = parser.Run(tokens);
	}

	return 0;
}
