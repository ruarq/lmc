#include "Locale.hpp"

namespace Lm::Locale
{

auto Country() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(3, 2);
}

auto Language() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(0, 2);
}

auto Encoding() -> std::string
{
	const auto lang = GetEnv("LANG");
	if (lang.empty())
	{
		return "";
	}

	return lang.substr(lang.find_last_of('.') + 1);
}

}
