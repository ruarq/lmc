/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#pragma once

#include <string>
#include <vector>

#include "Option.hpp"

namespace Lm::Opt
{

/**
 * @brief Parse argc & argv
 * @return All non-option argument in argv
 */
auto Parse(const std::vector<std::string> &argv, const std::vector<Option> &options) -> std::vector<std::string>;

/**
 * @brief Called by Lm::Opt::Parse
 * @return True if the option at arg was an option, false if not
 */
auto ParseOption(const std::vector<std::string> &argv, size_t &arg, const std::vector<Option> &options) -> bool;

/**
 * @brief Called by Lm::Opt::ParseOption
 */
auto InvokeOption(const std::vector<std::string> &argv, size_t &arg, const Option &option) -> void;

/**
 * @brief Generate a help text based on a list of options
 */
auto GenerateHelpText(const std::vector<Option> &options) -> std::string;

}
