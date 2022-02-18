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
	file = fopen(filename.c_str(), "r");
	if (!file)
	{
		LM_DEBUG("Couldn't open file '{}'", filename);
		return;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	buf = new char[size + 1];
	buf[size] = '\0';
	fread(buf, sizeof(char), size, file);
}

File::~File()
{
	if (buf)
	{
		delete[] buf;
	}

	fclose(file);
}

auto File::Buf() const -> const char *
{
	return buf;
}

auto File::Name() const -> std::string
{
	return name;
}

auto File::Size() const -> size_t
{
	return size + 1; // in File::File(const std::string &) we allocate size + 1 because of the null-terminator
}

}
