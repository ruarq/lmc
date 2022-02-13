/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#include "Locale.hpp"

namespace Lm
{

std::unordered_map<std::string, std::string> Locale::phrases;

auto Locale::Full() -> std::string
{
	return GetEnv("LANG");
}

auto Locale::Country() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(3, 2);
}

auto Locale::Language() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(0, 2);
}

auto Locale::Encoding() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(lang.find_last_of('.') + 1);
}

auto Locale::LoadFromFile(const std::string &filename) -> bool
{
	auto ParseLine = [](const std::string &line) {
		if (line.empty())
		{
			return;
		}

		const auto key = line.substr(0, line.find_first_of(" \t"));
		const auto value = line.substr(line.find_first_of(" \t"));

		phrases[key] = value.substr(value.find_first_not_of(" \t"));
	};

	std::ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		ParseLine(line);
	}

	return true;
}

auto Locale::Get(const std::string &phrase) -> const std::string &
{
#if defined(DEBUG)
	if (phrases.find(phrase) == phrases.end())
	{
		LM_DEBUG("No such key '{}' in phrases", phrase);
	}
#endif

	return phrases.at(phrase);
}

}
