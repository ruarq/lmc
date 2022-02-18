/**
 * @author ruarq
 * @date 14.02.2022 
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

#include <fmt/color.h>
#include <fmt/format.h>

#include "Localization/Locale.hpp"

#ifdef DEBUG
	#define LM_DEBUG(fmt, ...) Lm::Logger::Debug(fmt, __VA_ARGS__)
#else
	#define LM_DEBUG(fmt, ...)
#endif

namespace Lm
{

class Logger final
{
public:
	static constexpr auto debugColor = fmt::color::yellow;
	static constexpr auto infoColor = fmt::color::green_yellow;
	static constexpr auto errorColor = fmt::color::red;

public:
	/**
	 * @brief Log a debug message
	 */
	template<typename... Args>
	static auto Debug(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n",
			fmt::format(fmt::fg(debugColor), "[DEBUG]"),
			fmt::format(fmt, args...));
	}

	/**
	 * @brief Log some (arbitrary) information
	 */
	template<typename... Args>
	static auto Info(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n", fmt::format(fmt::fg(infoColor), "[INFO]"), fmt::format(fmt, args...));
	}

	/**
	 * @brief Log a error message
	 */
	template<typename... Args>
	static auto Error(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n",
			fmt::format(fmt::fg(errorColor), "{}:", Locale::Get("ERROR")),
			fmt::format(fmt, args...));
	}
};

}
