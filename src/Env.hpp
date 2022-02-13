/**
 * @author ruarq
 * @date 11.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#pragma once

#include <string>

namespace Lm
{

/**
 * @brief Get the environment variable value for "env"
 */
auto GetEnv(const std::string &env) -> std::string;

}
