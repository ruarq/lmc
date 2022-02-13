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

#include <string>

#include <fmt/format.h>

#include "File.hpp"
#include "Lexer/Lexer.hpp"
#include "Localization/Locale.hpp"
#include "Opt/Parse.hpp"

using namespace std::string_literals;

// TODO(ruarq): File a bug report about this, clang format formats
// "auto main(int argc, char **argv) -> int"
// to
// "automain(int argc, char **argv) -> int"
// auto main(int argc, char **argv) -> int
int main(int argc, char **argv)
{
	Lm::Locale::LoadFromFile("data/locales/"s + Lm::Locale::Full());

	// We need the help text in the "help" option, but
	// we can only generate it after declaring the option
	// array.
	std::string helpText;

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

	const auto filenames = Lm::Opt::Parse(std::vector<std::string>(argv, argv + argc), options);

	for (const auto &filename : filenames)
	{
		const Lm::File file(filename);

		Lm::Lexer lexer;
		const auto tokens = lexer.Run(file);

		for (const auto &token : tokens)
		{
			fmt::print("{:3} {:4}\n", (std::uint32_t)(token.type), token.literal);
		}
	}

	return 0;
}
