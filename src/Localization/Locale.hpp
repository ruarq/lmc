/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#pragma once

#include <array>
#include <fstream>
#include <string>
#include <unordered_map>

#include <fmt/format.h>

#include "../Env.hpp"
#include "../Log/Debug.hpp"

namespace Lm
{

class Locale final
{
public:
	/**
	 * @brief Get the full locale
	 */
	static auto Full() -> std::string;

	/**
	 * @brief Get the country
	 */
	static auto Country() -> std::string;

	/**
	 * @brief Get the language
	 */
	static auto Language() -> std::string;

	/**
	 * @brief Get the encoding
	 */
	static auto Encoding() -> std::string;

public:
	/**
	 * @brief Load the locale from a file
	 * @return Whether loading was successful or not
	 */
	static auto LoadFromFile(const std::string &filename) -> bool;

	/**
	 * @brief Get a phrase from the locale
	 */
	static auto Get(const std::string &phrase) -> const std::string &;

private:
	static std::unordered_map<std::string, std::string> phrases;
};

}
