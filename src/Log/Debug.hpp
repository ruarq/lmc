/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
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
