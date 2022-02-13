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
