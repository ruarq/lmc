/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#include "Env.hpp"

#include <cstdlib>

namespace Lm
{

auto GetEnv(const std::string &env) -> std::string
{
	return std::getenv(env.c_str()) ?: std::string {};
}

}
