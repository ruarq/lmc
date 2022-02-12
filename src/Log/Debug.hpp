/**
 * @author ruarq
 * @date 12.02.2022 
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

#if defined(DEBUG)
	#include <fmt/format.h>
	#include <fmt/color.h>

	#define LM_DEBUG(fmtstr, ...) \
		fmt::print("{} {} {}\n", \
			fmt::format(fmt::fg(fmt::color::yellow), "[DEBUG]"), \
			fmt::format(fmt::emphasis::bold, "{}:{}:", __FILE__, __LINE__), \
			fmt::format("{}", fmt::format(fmtstr, __VA_ARGS__)));
#else
	#define LM_DEBUG(fmtstr, ...)
#endif
