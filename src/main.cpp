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

#include <string>

#include <fmt/format.h>

#include "File.hpp"
#include "Lexer/Lexer.hpp"
#include "Localization/Locale.hpp"
#include "Opt/Parse.hpp"
#include "hcd/LicenseText.hpp"
#include "hcd/WarrantyText.hpp"

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
			"license",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				fmt::print("{}\n", Lm::licenseText);
				std::exit(0);
			},
			Lm::Locale::Get("HELP_LICENSE_DESCRIPTION")
		},
		{
			"warranty",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				fmt::print("{}\n", Lm::warrantyText);
				std::exit(0);
			},
			Lm::Locale::Get("HELP_WARRANTY_DESCRIPTION")
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
			fmt::print("{} '{}'\n", (size_t)(token.type), token.literal);
		}
	}

	return 0;
}
