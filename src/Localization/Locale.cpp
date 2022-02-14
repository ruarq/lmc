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

#include "Locale.hpp"

#include "../Logger.hpp"

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
#ifdef DEBUG
	if (phrases.find(phrase) == phrases.end())
	{
		LM_DEBUG("No such key '{}' in phrases", phrase);
	}
#endif

	return phrases.at(phrase);
}

}
