/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#pragma once

#include <fstream>
#include <string>

namespace Lm
{

/**
 * @brief Simple file information
 */
class File final
{
public:
	/**
	 * @brief Load from file
	 * @param filename The name of the file
	 */
	File(const std::string &filename);

public:
	std::string name;
	std::string content;
};

/**
 * @brief Store a location in a file
 */
struct FileLoc final
{
	size_t line = 0;
	size_t column = 0;
};

}
