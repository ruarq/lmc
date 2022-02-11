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

#include <iostream>
#include <string>

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
	Lm::Locale locale;
	locale.LoadFromFile("data/locales/"s + Lm::Locale::Get());

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
				std::cout << "Version\n";
				std::exit(0);
			},
			locale.GetPhrase("HelpVersionDescription")
		},
		{
			"license",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				std::cout << Lm::licenseText << "\n";
				exit(0);
			},
			locale.GetPhrase("HelpLicenseDescription")
		},
		{
			"warranty",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				std::cout << Lm::warrantyText << "\n";
				exit(0);
			},
			locale.GetPhrase("HelpWarrantyDescription")
		},
		{
			"locale",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[](const std::string &) {
				const auto language = Lm::Locale::Language();
				const auto country = Lm::Locale::Country();
				const auto encoding = Lm::Locale::Encoding();

				if (!language.empty() && !country.empty() && !encoding.empty())
				{
					std::cout << language << "_" << country << "." << encoding << "\n";
					exit(0);
				}
				else
				{
					std::cout << "There was a problem.\nLANG=" << Lm::GetEnv("LANG") << "\n";
					exit(1);
				}
			},
			locale.GetPhrase("HelpLocaleDescription")
		},
		{
			"help",
			Lm::Opt::Option::noShortOption,
			Lm::Opt::Option::Argument::None,
			[&helpText, &argv, &locale](const std::string &) {
				std::cout << locale.GetPhrase("Usage") << ": " << argv[0] << " [" << locale.GetPhrase("Options") << "] " << locale.GetPhrase("File") << "...\n";
				std::cout << locale.GetPhrase("Options") << ":\n";
				std::cout << helpText << "\n";
			},
			locale.GetPhrase("HelpHelpDescription")
		}
	// clang-format on
	};

	// Generate help text
	helpText = Lm::Opt::GenerateHelpText(options);

	const auto files = Lm::Opt::Parse(std::vector<std::string>(argv, argv + argc), options);

	for (const auto &file : files)
	{
		std::cout << file << "\n";
	}

	return 0;
}
