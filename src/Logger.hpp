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

#include "File.hpp"
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

	static constexpr auto infoColor = fmt::color::green;

	static constexpr auto warningColor = fmt::color::violet;
	static constexpr auto warningEmphasis = fmt::emphasis::bold;

	static constexpr auto errorColor = fmt::color::red;
	static constexpr auto errorEmphasis = fmt::emphasis::bold;

	static constexpr auto fileEmphasis = fmt::emphasis::bold;

public:
	template<typename... Args>
	static auto Debug(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n",
			fmt::format(fmt::fg(debugColor), "[DEBUG]"),
			fmt::format(fmt, args...));
	}

	template<typename... Args>
	static auto Info(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n",
			fmt::format(fmt::fg(infoColor), "{}:", Locale::Get("INFO")),
			fmt::format(fmt, args...));
	}

	template<typename... Args>
	static auto Warning(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n",
			fmt::format(fmt::fg(warningColor) | warningEmphasis, "{}:", Locale::Get("WARNING")),
			fmt::format(fmt, args...));
	}

	template<typename... Args>
	static auto WarningFile(const std::string &filename,
		const File::Pos &pos,
		const std::string &fmt,
		Args &&...args) -> void
	{
		Warning("{} {}",
			fmt::format(fileEmphasis, "{}:{}:{}:", filename, pos.line, pos.column),
			fmt::format(fmt, args...));
	}

	template<typename... Args>
	static auto Error(const std::string &fmt, Args &&...args) -> void
	{
		fmt::print("{} {}\n",
			fmt::format(fmt::fg(errorColor) | errorEmphasis, "{}:", Locale::Get("ERROR")),
			fmt::format(fmt, args...));
	}

	template<typename... Args>
	static auto ErrorFile(const std::string &filename,
		const File::Pos &pos,
		const std::string &fmt,
		Args &&...args) -> void
	{
		Error("{} {}",
			fmt::format(fileEmphasis, "{}:{}:{}:", filename, pos.line, pos.column),
			fmt::format(fmt, args...));
	}

private:
	static std::string programPath;
};

}
