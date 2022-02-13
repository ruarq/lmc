/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#include "File.hpp"

namespace Lm
{

File::File(const std::string &filename)
	: name(filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return;
	}

	// TODO(ruarq): Faster solution
	std::string line;
	while (std::getline(file, line))
	{
		content += line + std::string("\n");
	}
}

}
