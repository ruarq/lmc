/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
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
