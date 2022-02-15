/**
 * @author ruarq
 * @date 12.02.2022 
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

#include "File.hpp"

#include "Logger.hpp"

namespace Lm
{

File::File(const std::string &filename)
	: name(filename)
{
	std::FILE *file = fopen(filename.c_str(), "r");
	if (!file)
	{
		LM_DEBUG("Couldn't open file '{}'", filename);
		return;
	}

	fseek(file, 0, SEEK_END);
	const auto fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	content = std::string(fileSize, 0);

	const auto bytesRead = fread(content.data(), sizeof(char), fileSize, file);
	LM_DEBUG("Read {} bytes from '{}'", bytesRead, filename);

	fclose(file);
}

}
