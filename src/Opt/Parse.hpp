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

#pragma once

#include <string>
#include <vector>

#include "Option.hpp"

namespace Lm::Opt
{

/**
 * @brief parse argc & argv
 * @return all non-option argument in argv
 */
auto Parse(const std::vector<std::string> &argv, const std::vector<Option> &options) -> std::vector<std::string>;

/**
 * @brief Called by Lm::Opt::Parse
 * @return true if the option at arg was an option, false if not
 */
auto ParseOption(const std::vector<std::string> &argv, size_t &arg, const std::vector<Option> &options) -> bool;

/**
 * @brief Called by Lm::Opt::ParseOption
 */
auto InvokeOption(const std::vector<std::string> &argv, size_t &arg, const Option &option) -> void;

}
